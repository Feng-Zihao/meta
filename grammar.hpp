
#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <iostream>
#include <string>
#include <functional>
#include <boost/regex.hpp>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <deque>

using namespace std;


class Token {
public:
    Token(string _name, string _expr);
    
    const string name;
    const string expr;
    const boost::regex rgx;
};

class RuleNode {
public:
    RuleNode(string _value, string _separator, int _chain_type);

    bool isTokenName();
    bool isKeyword();

    static const int kCanIgnored = 0;
    static const int kAtLeastOnce = 1;

    const string value;
    const string separator;
    const int chain_type;
    
};


class Rule {
public:
    set<string> start_symbols;
    vector<RuleNode> nodes;
};


typedef unordered_map<string, Token, hash<string>> TokenMap;
typedef unordered_map<string, Rule, hash<string>> RuleMap;
typedef unordered_set<string, hash<string>> KeywordSet;

class Parser {
public:

    bool ReadGrammarFile(string path);

    TokenMap token_map = TokenMap(1024);
    RuleMap rule_map = RuleMap(1024);
    KeywordSet keyword_set = KeywordSet(1024);


private:
    typedef pair<string, Token> TokenMapPair;
    TokenMapPair declToken(string name, string expr) {
        return make_pair(name, Token(name, expr));
    }
};
#endif
