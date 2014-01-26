%option outfile="lex.c"
%option header-file="lex.h"
%option 8bit
%option stack
%option yylineno
%option noyywrap
%option pointer
%option reentrant
%option bison-bridge


%top{
#include "def.h"
#include "gram.h"
}

utf8_c [\x09\x0A\x0D\x20-\x7E]|[\xC2-\xDF][\x80-\xBF]|\xE0[\xA0-\xBF][\x80-\xBF]|[\xE1-\xEC\xEE\xEF]([\x80-\xBF]{2})|\xED[\x80-\x9F][\x80-\xBF]|\xF0[\x90-\xBF]([\x80-\xBF]{2})|[\xF1-\xF3]([\x80-\xBF]{3})|\xF4[\x80-\x8F]([\x80-\xBF]{2})

%%


(\+|\-)?[[:digit:]]+ {return TOK_INT;}
(\+|\-)?[[:digit:]]+\.[[:digit:]]*((e|E)(\+|\-)?[[:digit:]]+)? {return TOK_FLOAT;}
(\+|\-)?[[:digit:]]*\.[[:digit:]]+((e|E)(\+|\-)?[[:digit:]]+)? {return TOK_FLOAT;}
[_[:alpha:]][_[:alnum:]]+ {return TOK_ID;}



%%


