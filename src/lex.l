%option outfile="lex.c"
%option header-file="lex.h"
%option 8bit
%option stack
%option yylineno
%option noyywrap
%option pointer
%option reentrant
%option bison-bridge
%option bison-locations
%option stack

%top{
#include <stdio.h>
#include <string.h>
#include "gram.h"
#include "semt.h"

#define YY_HEADER_EXPORT_START_CONDITIONS

void yy_push_state (int new_state ,void* yyscanner);
void yy_pop_state (void* yyscanner);
int yy_top_state (void* yyscanner);

#define YY_INC_YYLOC yylloc_param->first_column+=yyleng

}

utf8_c [\x09\x0A\x0D\x20-\x7E]|[\xC2-\xDF][\x80-\xBF]|\xE0[\xA0-\xBF][\x80-\xBF]|[\xE1-\xEC\xEE\xEF]([\x80-\xBF]{2})|\xED[\x80-\x9F][\x80-\xBF]|\xF0[\x90-\xBF]([\x80-\xBF]{2})|[\xF1-\xF3]([\x80-\xBF]{3})|\xF4[\x80-\x8F]([\x80-\xBF]{2})


newline (\n\r)|(\r\n)|(\n)|(\r)

%x NEWLINE_SENSITIVE
%x ACCEPT_RIGHT_ANGLE_BRACKET

%%


<INITIAL,ACCEPT_RIGHT_ANGLE_BRACKET>{
class   {YY_INC_YYLOC; return KW_CLASS;}
func    {YY_INC_YYLOC; return KW_FUNC;}
while   {YY_INC_YYLOC; return KW_WHILE;}
for     {YY_INC_YYLOC; return KW_FOR;}
if      {YY_INC_YYLOC; return KW_IF;}
elif    {YY_INC_YYLOC; return KW_ELIF;}
else    {YY_INC_YYLOC; return KW_ELSE;}
int     {YY_INC_YYLOC; return KW_INT;}
float   {YY_INC_YYLOC; return KW_FLOAT;}
string  {YY_INC_YYLOC; return KW_STRING;}
return  {YY_INC_YYLOC; return KW_RETURN;}
null    {YY_INC_YYLOC; return KW_NULL;}
\(|\)|\{|\}|\[|\]       {YY_INC_YYLOC; return yytext[0];}
;|!|,|\.|>|<|=              {YY_INC_YYLOC; return yytext[0];}
\+|-|\*|\/|\%|\&|\||\^  {YY_INC_YYLOC; return yytext[0];}

\<<=        {YY_INC_YYLOC; return OP_SHL_EQ;}
\>>=        {YY_INC_YYLOC; return OP_SHR_EQ;}
\<<<=       {YY_INC_YYLOC; return OP_ROL_EQ;}
\>>>=       {YY_INC_YYLOC; return OP_ROR_EQ;}
\|\|\=      {YY_INC_YYLOC; return OP_OR_EQ;}
\+=         {YY_INC_YYLOC; return OP_ADD_EQ;}
-=          {YY_INC_YYLOC; return OP_SUB_EQ;}
\*=         {YY_INC_YYLOC; return OP_MUL_EQ;}
\/=         {YY_INC_YYLOC; return OP_DIV_EQ;}
%=          {YY_INC_YYLOC; return OP_MOD_EQ;}
\**=        {YY_INC_YYLOC; return OP_POW_EQ;}

\<<         {YY_INC_YYLOC; return OP_SHL;}
\<<<        {YY_INC_YYLOC; return OP_ROL;}

\**         {YY_INC_YYLOC; return OP_POW;}
&&          {YY_INC_YYLOC; return OP_LOGIC_AND;}
\|\|        {YY_INC_YYLOC; return OP_LOGIC_OR;}

==          {YY_INC_YYLOC; return OP_CMP_EQ;}
\<=         {YY_INC_YYLOC; return OP_LE;}
\>=         {YY_INC_YYLOC; return OP_GE;}
!=          {YY_INC_YYLOC; return OP_NE;}


(\+|\-)?[[:digit:]]+        {YY_INC_YYLOC; return TOK_INT;}
(\+|\-)?[[:digit:]]+\.[[:digit:]]*((e|E)(\+|\-)?[[:digit:]]+)? {YY_INC_YYLOC; return TOK_FLOAT;}
(\+|\-)?[[:digit:]]*\.[[:digit:]]+((e|E)(\+|\-)?[[:digit:]]+)? {YY_INC_YYLOC; return TOK_FLOAT;}
[_[:alpha:]][_[:alnum:]]*   {YY_INC_YYLOC; return TOK_ID;}

{newline}   {
    yylloc_param->first_column = 0;
    yylloc_param->first_line++;
    }
[[:space:]]     {
    YY_INC_YYLOC;
    }

.   {return 0;}

}

<INITIAL>{
\>>>        {YY_INC_YYLOC; return OP_ROR;}
\>>         {YY_INC_YYLOC; return OP_SHR;}
}

<ACCEPT_RIGHT_ANGLE_BRACKET>{
\>>>        {REJECT;}
\>>         {REJECT;}
}
%%

