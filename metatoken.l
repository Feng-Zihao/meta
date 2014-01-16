%option reentrant stack noyywrap
%top{
#include "meta.h"
}

DIGIT [0-p]
ID    [_a-zA-Z][_a-zA-Z0-9]*
WHITESPACE [ \f\t\v\n\r]
NEWLINE    (\r\n)|\n

%%

"if"
"elif"
"else"
"struct"
"func"

"int"
"double"
"string"

"+"
"-"
"*"
"/"
"//"

"+="
"-="
"*="
"/="

">"
"<"
">="
"<="
"=="
"!="

"&"
"|"
"^"

"!"
"."


%%


