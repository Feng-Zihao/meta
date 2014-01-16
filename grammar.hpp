
#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <iostream>
#include <string>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <deque>
#include <memory>
#include <boost/regex.hpp>
using namespace std;


class Symbol {
public:
    static Symbol Regex(string _expr);

    void InitFromRuleExpr(string& rule_expr);
    bool isKeyword();
    bool isNonTerminal();

    // value for symbol_type
    static const int kTerminal = 0;
    static const int kNonTerminal = 1;

    // value for chain_type
    static const int kCanSkip;
    static const int kOnlyOnce;
    static const int kAtLeastOnce;

    string value;
    int symbol_type;
    int terminal_type;
    boost::regex re;

    unique_ptr<Symbol> separator = nullptr;
    int chain_type = Symbol::kOnlyOnce;
private:
    void update_symbol_type();
};


class Rule {
public:
    vector<Symbol> symbol_chains;
    set<Symbol> start_symbols;  // tokens, keywords or specific characters
};


class RuleGroup {
public:
    string name;
    vector<Rule> rules;
    set<Symbol> start_symbols;
};


typedef map<string, Symbol> TSymMap;
class Parser {
public:

    bool ReadGrammarFile(string path);

    TSymMap terminal_symbol_map;
};

string GetOneSymbolExpr(const string& rule_expr);

#endif
