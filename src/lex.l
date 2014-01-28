%option outfile="lex.c"
%option header-file="lex.h"
%option 8bit
%option stack
%option yylineno
%option noyywrap
%option pointer
%option reentrant
%option bison-bridge
%option stack

%top{
#include <stdio.h>
#include "gram.h"

#define YYSTYPE char const *
#define YYLEX_PARAM   scanner

void yy_push_state (int new_state ,void* yyscanner);
void yy_pop_state (void* yyscanner);
int yy_top_state (void* yyscanner);

}

utf8_c [\x09\x0A\x0D\x20-\x7E]|[\xC2-\xDF][\x80-\xBF]|\xE0[\xA0-\xBF][\x80-\xBF]|[\xE1-\xEC\xEE\xEF]([\x80-\xBF]{2})|\xED[\x80-\x9F][\x80-\xBF]|\xF0[\x90-\xBF]([\x80-\xBF]{2})|[\xF1-\xF3]([\x80-\xBF]{3})|\xF4[\x80-\x8F]([\x80-\xBF]{2})


newline (\n\r)|(\r\n)|\n|\r

%s FORCE_NEWLINE

%%



struct  {return KW_STRUCT;}
func    {return KW_FUNC;}
while   {return KW_WHILE;}
for     {return KW_FOR;}
if      {return KW_IF;}
elif    {return KW_ELIF;}
else    {return KW_ELSE;}
int     {return KW_INT;}
float   {return KW_FLOAT;}
string  {return KW_STRING;}
\(|\)|\{|\}|\[|\]       {return yytext[0];}
,|\.|>|<|=              {return yytext[0];}
\+|-|\*|\/|\%|\&|\||\^  {return yytext[0];}

\>>=        {return OP_SHR_EQ;}
\<<=        {return OP_SHL_EQ;}
\>>>=       {return OP_ROR_EQ;}
\<<<=       {return OP_ROL_EQ;}
\|\|\=      {return OP_OR_EQ;}
\+=         {return OP_ADD_EQ;}
-=          {return OP_SUB_EQ;}
\*=         {return OP_MUL_EQ;}
\/=         {return OP_DIV_EQ;}
%=          {return OP_MOD_EQ;}
\**=        {return OP_POW_EQ;}

\>>         {return OP_SHR;}
\<<         {return OP_SHL;}
\>>>        {return OP_ROR;}
\<<<        {return OP_ROL;}

\**         {return OP_POW;}
&&          {return OP_LOGIC_AND;}
\|\|        {return OP_LOGIC_OR;}

==          {return OP_CMP_EQ;}
\>=         {return OP_GE;}
\<=         {return OP_LE;}
!=          {return OP_NE;}


(\+|\-)?[[:digit:]]+        {return TOK_INT;}
(\+|\-)?[[:digit:]]+\.[[:digit:]]*((e|E)(\+|\-)?[[:digit:]]+)? {return TOK_FLOAT;}
(\+|\-)?[[:digit:]]*\.[[:digit:]]+((e|E)(\+|\-)?[[:digit:]]+)? {return TOK_FLOAT;}
[_[:alpha:]][_[:alnum:]]*   {return TOK_ID;}

<FORCE_NEWLINE>{newline}    {printf("force newline\n");yy_pop_state(yyscanner);return TOK_NEWLINE;}

{newline}                   {;}
[[:space:]]                 {;}


%%


