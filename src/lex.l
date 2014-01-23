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

utf8_c [\x09\x0A\x0D\x20-\x7E]|[\xC2-\xDF][\x80-\xBF]|\xE0[\xA0-\xBF][\x80-\xBF]|[\xE1-\xEC\xEE\xEF]([\x80-\xBF]{2})|\xED[\x80-\x9F][\x80-\xBF]|\xF0[\x90-\xBF]([\x80-\xBF]{2})|[\xF1-\xF3]([\x80-\xBF]{3})|\xF4[\x80-\x8F]([\x80-\xBF]{2})

%%

"if"        {return KW_IF;}
"elif"      {return KW_ELIF;}
"else"      {return KW_ELSE;}
"for"       {return KW_FOR;}
"while"     {return KW_WHILE;}


"struct"    {return KW_STRUCT;}
"func"      {return KW_FUNC;}

"int"       {return KW_INT;}
"double"    {return KW_DOUBLE;}
"string"    {return KW_STRING;}

"+"         {return SYM_ADD;}
"-"         {return SYM_SUB;}
"*"         {return SYM_MUL;}
"/"         {return SYM_DIV;}
"**"        {return SYM_POW;}

"+="        {return SYM_ADD_EQ;}
"-="        {return SYM_SUB_EQ;}
"*="        {return SYM_MUL_EQ;}
"/="        {return SYM_DIV_EQ;}
"%="        {return SYM_MOD_EQ;}
"**="       {return SYM_POW_EQ;}

">"         {return SYM_GT;}
"<"         {return SYM_LT;}
">="        {return SYM_GE;}
"<="        {return SYM_LE;}
"=="        {return SYM_EQ;}
"!="        {return SYM_NE;}

"&"         {return SYM_BIT_AND;}
"|"         {return SYM_BIT_OR;}
"^"         {return SYM_BIT_XOR;}

"!"         {return SYM_NOT;}
"."         {return SYM_DOT;}
","         {return SYM_COMMA;}


(\+|\-)?[[:digit:]]+ {return TOK_INT;}
(\+|\-)?[[:digit:]]+\.[[:digit:]]*((e|E)(\+|\-)?[[:digit:]]+)? {return TOK_FLOAT;}
(\+|\-)?[[:digit:]]*\.[[:digit:]]+((e|E)(\+|\-)?[[:digit:]]+)? {return TOK_FLOAT;}
[_[:alpha:]][_[:alnum:]]+ {return TOK_ID;}



%%


