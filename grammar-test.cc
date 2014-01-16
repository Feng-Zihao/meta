
#include "grammar.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <functional>
#include <string>
using namespace std;

TEST(SymbolTest, rule_parsing) {
    Symbol sym;
    string s;
    s.assign("abc{efg}");
    sym.InitFromRuleExpr(s);
    EXPECT_EQ("abc", sym.value);
    EXPECT_EQ(false, sym.isNonTerminal());
    EXPECT_EQ(false, sym.isKeyword());
    EXPECT_EQ(Symbol::kCanSkip, sym.chain_type);
    EXPECT_EQ("efg", sym.separator->value);

    s.assign("abc");
    sym.InitFromRuleExpr(s);
    EXPECT_EQ("abc", sym.value);
    EXPECT_EQ(Symbol::kOnlyOnce, sym.chain_type); 
    EXPECT_EQ(nullptr, sym.separator);

    s.assign("'func'[',']");
    sym.InitFromRuleExpr(s);
    EXPECT_EQ("'func'", sym.value);
    EXPECT_EQ(false, sym.isNonTerminal());
    EXPECT_EQ(true, sym.isKeyword());
    EXPECT_EQ(Symbol::kAtLeastOnce, sym.chain_type);
    EXPECT_EQ("','", sym.separator->value);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    //Parser parser;
    //parser.ReadGrammarFile("./meta_v0_0_0.grammar");
    return RUN_ALL_TESTS();
}
