
#include "grammar.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <functional>
#include <string>
using namespace std;

//TEST(simple, simple) {
//    EXPECT_EQ(1, 1);
//}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    Parser parser;
    parser.ReadGrammarFile("./meta_v0_0_0.grammar");
    return RUN_ALL_TESTS();
}
