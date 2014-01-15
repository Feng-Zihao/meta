
#include "grammar.hpp"
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;


Symbol Symbol::Regex(string _expr)
{
    Symbol sym;
    sym.symbol_type = kTerminal;
    sym.re = boost::regex(_expr);
    return sym;
}


Symbol Symbol::Keyword(string _value)
{
    Symbol sym;
    sym.symbol_type = kTerminal;
    sym.terminal_type = kKeyword;
    sym.value = _value;
    sym.re = boost::regex(_value);
    return sym;
}


Symbol Symbol::SpecialCharacter(string _value)
{
    Symbol sym;
    sym.symbol_type = kTerminal;
    sym.terminal_type = kSpecialCharacter;
    sym.value = _value;
    sym.re = boost::regex(_value);
    return sym;
}


Symbol Symbol::Nonterminal(string _value)
{
    Symbol sym;
    sym.symbol_type = kNonTerminal;
    sym.value = _value;
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
            *lsit++;
            cout << curr_key << endl;
            continue;
        }

        string rule_expr(*lsit);
        *lsit++;

        //Rule rule;
        boost::trim(rule_expr);
        while (!rule_expr.empty()) {
            string main = GetOneSymbolExpr(rule_expr);
            rule_expr.erase(0, main.length());
            string separator;
            if (!rule_expr.empty()) {
                if (rule_expr[0] == '[') {
                    rule_expr.erase(0, 1);
                    separator = GetOneSymbolExpr(rule_expr);
                    rule_expr.erase(0, separator.length());
                    if (rule_expr[0] != ']') {
                        cerr << "error in grammar" << endl;
                        exit(EXIT_FAILURE);
                    }
                    rule_expr.erase(0, 1);
                } 
                if (rule_expr[0] == '{') {
                    rule_expr.erase(0, 1);
                    separator = GetOneSymbolExpr(rule_expr);
                    rule_expr.erase(0, separator.length());
                    if (rule_expr[0] != '}') {
                        cerr << "error in grammar" << endl;
                        exit(EXIT_FAILURE);
                    }
                    rule_expr.erase(0, 1);
                }
            }
            cout << main << ":" << separator << endl;
            boost::trim(rule_expr);
        }
    }
    

    
    return true;
}


string GetOneSymbolExpr(string& rule_expr)
{
    boost::smatch sm;
    if (rule_expr[0] == '\'') {
        boost::regex_search(rule_expr, sm, boost::regex("'[^[:space:]']+'"));
    } else {
        boost::regex_search(rule_expr, sm, boost::regex("[a-zA-Z]+"));
    }
    return sm.str();
}
