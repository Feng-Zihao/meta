%option reentrant
%option outfile="lex.c"
%option header-file="lex.h"
%option 8bit
%option stack
%option yylineno
%option noyywrap
%option pointer
%top{
#include "parser.h"
#include "def.h"
}

DIGIT [0-p]
ID    [_a-zA-Z][_a-zA-Z0-9]*
WHITESPACE [ \f\t\v\n\r]
NEWLINE    (\r\n)|\n

%%

"if"        KW_IF;
"elif"      KW_ELIF;
"else"      KW_ELSE;
"struct"    KW_STRUCT;
"func"      KW_FUNC;

"int"       KW_INT;
"double"    KW_DOUBLE;
"string"    KW_STRING;

"+"         SYM_ADD;
"-"         SYM_SUB;
"*"         SYM_MUL;
"/"         SYM_DIV;
"**"        SYM_POW;

"+="        SYM_ADD_EQ;
"-="        SYM_SUB_EQ;
"*="        SYM_MUL_EQ;
"/="        SYM_DIV_EQ;
"%="        SYM_MOD_EQ;
"**="       SYM_POW_EQ;

">"         SYM_GT;
"<"         SYM_LT;
">="        SYM_GE;
"<="        SYM_LE;
"=="        SYM_EQ;
"!="        SYM_NE;

"&"         SYM_BIT_AND;
"|"         SYM_BIT_OR;
"^"         SYM_BIT_XOR;

"!"         SYM_NOT;
"."         SYM_DOT;
","         SYM_COMMA;


%%


