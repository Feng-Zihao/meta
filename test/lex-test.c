
#include <stdlib.h>
#include <stdio.h>
#include "lex.h"
#include "ctest.h"



void test_lexer_only() { 
    yyscan_t scanner;
    YY_BUFFER_STATE buf;
    int tmprs;

    YYSTYPE yystype;
#define __LEX_TEST(str, ret);\
    yylex_init(&scanner);\
    buf = yy_scan_string(str, scanner);\
    tmprs = yylex(&yystype, scanner);\
    CASSERT_EQ( tmprs, ret );\
    CASSERT_STR_EQ( yyget_text(scanner), str );\
    yy_delete_buffer(buf, scanner);\
    yylex_destroy(scanner);\

    struct {
        char *str; int tok;
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

        {"struct", KW_STRUCT},
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

int main(int argc, const char *argv[])
{ 
    CTEST_FUNC(test_lexer_only);

    yyscan_t scanner;
 
    yylex_init(&scanner);
    yy_push_state(2, scanner);
    yy_push_state(3, scanner);
    yy_push_state(4, scanner);
    printf("%d\n", yy_top_state(scanner));
    yy_pop_state(scanner);
    printf("%d\n", yy_top_state(scanner));
    yy_pop_state(scanner);
    printf("%d\n", yy_top_state(scanner));
    yy_pop_state(scanner);
    yylex_destroy(scanner);


    return 0;
}
