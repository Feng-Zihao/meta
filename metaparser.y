%include {  #
#include <stdio.h>
#include <assert.h>
#include "metaparser.h"
#include "metadef.h"
}

%token_type {const char*}

%syntax_error {
    fprintf(stderr, "Error parsing command\n");
}

%name Meta
/*%start_symbol prog*/

%left MUL  DIV.
%left PLUS MINUS.
%left AND.
%left OR.
%left NOT.
%right RPARENTHESES.


value(A) ::= NULL(B). {}
value(A) ::= STRING(B). {}
value(A) ::= INT(B). {}
value(A) ::= ID(B). {}
value(A) ::= LPARENTHESES value(B) RPARENTHESES. {}
/*value(A) ::= value(B) PLUS value(C) . {}*/
/*value(A) ::= NOT value(B). {}*/
