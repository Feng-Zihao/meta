
#include <stdlib.h>
#include <stdio.h>
#include <gtest/gtest.h>
#include <string>
#include "parser.h"


using namespace std;

yyscan_t scanner;
YY_BUFFER_STATE buf;
int tmprs;

YYSTYPE lval;
YYLTYPE lloc;

#define __LEX_TEST(str, tok) \
    yylex_init(&scanner);\
    buf = yy_scan_string(str, scanner);\
    tmprs = yylex(&lval, &lloc, scanner);\
    EXPECT_EQ( tmprs, tok );\
    EXPECT_STREQ( yyget_text(scanner), str );\
    yy_delete_buffer(buf, scanner);\
    yylex_destroy(scanner);


TEST(LEX_TEST, LEX_TEST){

    struct {
        const char *str;
        int tok;
    } args[] = {
        {"090123123", TOK_INT},
        {"+090123123", TOK_INT},
        {"-0", TOK_INT},
        {"0", TOK_INT},


        {"+0.", TOK_FLOAT},
        {"-1.23", TOK_FLOAT},
        {"-1.23e1", TOK_FLOAT},
        {"-1.23e10", TOK_FLOAT},
        {"-1.23e-10", TOK_FLOAT},
        {"-1.23e+10", TOK_FLOAT},

        {".0", TOK_FLOAT},
        {"-.0", TOK_FLOAT},
        {"-.0123", TOK_FLOAT},
        {"-.0123e1", TOK_FLOAT},
        {"-.0123e+10", TOK_FLOAT},
        {"-.0123e-10", TOK_FLOAT},

        {"_abcd_1234123__", TOK_ID},

        {"class", KW_CLASS},
        {"func", KW_FUNC},
        {"for", KW_FOR},
        {"while", KW_WHILE},
        {"if", KW_IF},
        {"elif", KW_ELIF},
        {"else", KW_ELSE},
        {"int", KW_INT},
        {"float", KW_FLOAT},
        {"string", KW_STRING},

        {"(", '('},
        {")",')'},
        {"{", '{'},
        {"}", '}'},
        {"[", '['},
        {"]", ']'},
        {"+", '+'},
        {"-", '-'},
        {"*", '*'},
        {"/", '/'},
        {"%", '%'},
        {"&", '&'},
        {"|", '|'},
        {"^", '^'},
        {",", ','},
        {".", '.'},
        {"<", '<'},
        {">", '>'},
        {"=", '='},

        {"", 0}

    };

    int i = 0;
    for (; i < sizeof(args)/sizeof(args[0]); i++) {
        __LEX_TEST(args[i].str, args[i].tok);
    }
}


int main(int argc, char **argv)
{ 
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
