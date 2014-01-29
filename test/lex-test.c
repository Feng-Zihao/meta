
#include <stdlib.h>
#include <stdio.h>
#include "lex.h"
#include "ctest.h"

yyscan_t scanner;
YY_BUFFER_STATE buf;
int tmprs;

YYSTYPE lval;
YYLTYPE lloc;


void test_lexer_only() { 
#define __LEX_TEST(str, tok);\
    yylex_init(&scanner);\
    yylex_init_extra(0, &scanner);\
    buf = yy_scan_string(str, scanner);\
    tmprs = yylex(&lval, &lloc, scanner);\
    CASSERT_EQ( tmprs, tok );\
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

void test_lexer_start_condition()
{
    yylex_init(&scanner);
    yylex_init_extra(0, &scanner);
    yy_push_state(FORCE_NEWLINE, scanner);
    const char* str = "\n\r";
    buf = yy_scan_string(str, scanner);
    tmprs = yylex(&lval, &lloc, scanner);
    CASSERT_EQ( tmprs, TOK_NEWLINE);
    yy_delete_buffer(buf, scanner);
    yylex_destroy(scanner);
  
}

int main(int argc, const char *argv[])
{ 
    CTEST_FUNC(test_lexer_only);
    CTEST_FUNC(test_lexer_start_condition);

    return 0;
}
