
#include <stdlib.h>
#include <stdio.h>
#include "def.h"
#include "lex.h"
#include "ctest.h"



void test_lexer_only() { 
    yyscan_t scanner;
    YY_BUFFER_STATE buf;

    YYSTYPE yystype;
#define __LEX_TEST(str, ret);\
    yylex_init(&scanner);\
    buf = yy_scan_string(str, scanner);\
    CASSERT_EQ( yylex(&yystype, scanner), ret );\
    CASSERT_STR_EQ( yyget_text(scanner), str );\
    yy_delete_buffer(buf, scanner);\
    yylex_destroy(scanner);\

    struct {
        char *str; int tok;
    } args[] = {
        /*{"if", KW_IF},*/
        /*{"elif", KW_ELIF},*/
        /*{"else", KW_ELSE},*/
        /*{"for", KW_FOR},*/
        /*{"while", KW_WHILE},*/
        /*{"struct", KW_STRUCT},*/
        /*{"func", KW_FUNC},*/
        /*{"int", KW_INT},*/
        /*{"double", KW_DOUBLE},*/
        /*{"string", KW_STRING},*/

        /*{"+", SYM_ADD},*/
        /*{"-", SYM_SUB},*/
        /*{"*", SYM_MUL},*/
        /*{"/", SYM_DIV},*/
        /*{"**", SYM_POW},*/

        /*{"+=", SYM_ADD_EQ},*/
        /*{"-=", SYM_SUB_EQ},*/
        /*{"*=", SYM_MUL_EQ},*/
        /*{"/=", SYM_DIV_EQ},*/
        /*{"%=", SYM_MOD_EQ},*/
        /*{"**=", SYM_POW_EQ},*/

        /*{">", SYM_GT},*/
        /*{"<", SYM_LT},*/
        /*{">=", SYM_GE},*/
        /*{"<=", SYM_LE},*/
        /*{"==", SYM_EQ},*/
        /*{"!=", SYM_NE},*/

        /*{"&", SYM_BIT_AND},*/
        /*{"|", SYM_BIT_OR},*/
        /*{"^", SYM_BIT_XOR},*/

        /*{"!", SYM_NOT},*/
        /*{".", SYM_DOT},*/
        /*{",", SYM_COMMA},*/


        {"090123123", TOK_INT},
        {"+090123123", TOK_INT},
        {"-0", TOK_INT},


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
    return 0;
}
