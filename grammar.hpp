
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
#include <boost/regex.hpp>
using namespace std;


class Symbol {
public:
    static Symbol Regex(string _expr);
    static Symbol Keyword(string _value);
    static Symbol SpecialCharacter(string _value);
    static Symbol Nonterminal(string _value);

    static const int kTerminal = 0;
    static const int kNonTerminal  = 1;

    static const int kKeyword = 2;
    static const int kSpecialCharacter = 3;

    string value;
    int symbol_type;
    int terminal_type;
    boost::regex re;
};

class SymbolChain {
public:
    static const int kCanSkip;
    static const int kAtLeastOnce;
    static const int kOnlyOnce;
    Symbol main;
    Symbol separator;
    int chain_type;
};

class Rule {
public:
    vector<SymbolChain> symbol_chains;
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

private:
};

string GetOneSymbolExpr(string& rule_expr);

#endif
