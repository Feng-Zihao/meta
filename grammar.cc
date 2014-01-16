
#include "grammar.hpp"
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;

const int Symbol::kCanSkip = 0;
const int Symbol::kOnlyOnce = 1;
const int Symbol::kAtLeastOnce = 2;

Symbol Symbol::Regex(string _expr)
{
    Symbol sym;
    sym.symbol_type = kTerminal;
    sym.re = boost::regex(_expr);
    return sym;
}


bool Parser::ReadGrammarFile(string path)
{
    ifstream ifs(path, ios::binary|ios::in);
    string content;
    content.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());

    // remove comment
    content = boost::regex_replace(content, boost::regex("#[^\\n]*\\n"), "\n");
    content = boost::regex_replace(content,
                boost::regex("(([[:space:]]*\\n)|\\n)+"), "\n");
    content = boost::regex_replace(content, boost::regex("^[[:space:]]"), "");

    // split and remove meaning less lines
    deque<string> lines;
    boost::split(lines, content, boost::is_any_of("\n"));
    auto new_endit = remove_if(lines.begin(), lines.end(), [](string& x){
        return x.empty();
    });
    lines.erase(new_endit, lines.end());

    // parse token regex
    auto lsit = lines.begin();
    boost::regex re("^[a-z](.*)");
    while (lsit != lines.end() && boost::regex_match(*lsit, re)) {
        string key = *lsit;
        lsit++;
        string expr = *lsit;
        lsit++;
        boost::trim(expr);
        terminal_symbol_map[key] = Symbol::Regex(expr);
    }


    // parse rules
    re.assign("^[A-Z](.*)");
    string curr_key;
    while (lsit != lines.end()) {
        if (boost::regex_match(*lsit, re)) {
            curr_key = *lsit;
            curr_key.pop_back();
            *lsit++;
            continue;
        }

        string rule_expr(*lsit);
        *lsit++;

        //Rule rule;
        boost::trim(rule_expr);
        while (!rule_expr.empty()) {
            Symbol s;
            s.InitFromRuleExpr(rule_expr);
            //cout << "    " << s.value;
            //if (s.separator != nullptr) {
            //    cout << " :: " << s.separator->value;
            //}
            //cout << endl;
            boost::trim(rule_expr);
        }
    }

    return true;
}


string GetOneSymbolExpr(const string& rule_expr)
{
    boost::smatch sm;
    if (rule_expr[0] == '\'') {
        boost::regex_search(rule_expr, sm, boost::regex("'[^[:space:]']+'"));
    } else {
        boost::regex_search(rule_expr, sm, boost::regex("[a-zA-Z]+"));
    }
    return sm.str();
}


void Symbol::InitFromRuleExpr(string& rule_expr)
{
    value = move(GetOneSymbolExpr(rule_expr));
    chain_type = kOnlyOnce;
    separator = nullptr;
    rule_expr.erase(0, value.length());
    if (!rule_expr.empty()) {
        if (rule_expr[0] == '[') {
            chain_type = kAtLeastOnce;
            rule_expr.erase(0, 1);
            separator =  unique_ptr<Symbol>(new Symbol);
            separator->value = move(GetOneSymbolExpr(rule_expr));
            rule_expr.erase(0, separator->value.length());
            if (rule_expr[0] != ']') {
                cerr << "error in grammar" << endl;
                exit(EXIT_FAILURE);
            }
            rule_expr.erase(0, 1);
        }
        if (rule_expr[0] == '{') {
            chain_type = kCanSkip;
            rule_expr.erase(0, 1);
            separator = unique_ptr<Symbol>(new Symbol);
            separator->value = move(GetOneSymbolExpr(rule_expr));
            rule_expr.erase(0, separator->value.length());
            if (rule_expr[0] != '}') {
                cerr << "error in grammar" << endl;
                exit(EXIT_FAILURE);
            }
            rule_expr.erase(0, 1);
        }
    }
}


bool Symbol::isNonTerminal() {
    return boost::regex_search(value, boost::regex("[A-Z]"));
}

bool Symbol::isKeyword() {
    return boost::regex_match(value, boost::regex("'[a-z]+'"));
}
