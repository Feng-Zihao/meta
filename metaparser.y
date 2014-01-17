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
%start_symbol prog

/*%left COMMA DOT .*/
%left PLUS MINUS .
%left MUL  DIV .
%left OR .
%left AND .
%left DOT .
%nonassoc NOT .


prog ::= prog_block .
prog_block ::= prog_block prog_block .
prog_block ::= struct_decl .
prog_block ::= func_decl .
prog_block ::= .


func_decl ::= KW_FUNC ID LPARENTHESES var_decl_list RPARENTHESES var_type_list statement_block .


statement_block ::= LBRACE statement_list RBRACE .


statement_list ::= .
statement_list ::= statement .
statement_list ::= statement_list statement .


/*statement ::= for_stmt .*/
statement ::= while_stmt .
statement ::= if_stmt .


while_stmt ::= KW_WHILE value statement_block .


if_stmt    ::= KW_IF value statement_block elif_block_list else_block .
elif_block ::= KW_ELIF value statement_block .
elif_block_list ::= .
elif_block_list ::= elif_block .
elif_block_list ::= elif_block_list elif_block .
else_block ::= KW_ELSE statement_block .



struct_decl ::= KW_STRUCT ID LBRACE var_decl_list RBRACE .


var_decl_list ::= .
var_decl_list ::= var_decl .
var_decl_list ::= var_decl_list var_decl .


id_chain ::= ID .                      // aa.bb.cc.dd
id_chain ::= id_chain DOT ID .


id_list ::= ID .                       // aa, bb, cc, dd
id_list ::= id_list COMMA ID .


var_decl ::= var_typed_assigned_decl .
var_decl ::= var_untyped_assigned_decl .
var_decl ::= var_typed_unassigned_decl .


var_type ::= id_chain .   // xxx  xxx.xxx
var_type ::= var_type LBRACKET var_type_list RBRACKET .  // type_tmpl< type >
var_type_list ::= var_type .
var_type_list ::= var_type_list COMMA var_type .


var_typed_assigned_decl ::= var_type var_untyped_assigned_decl .
var_typed_unassigned_decl ::= var_type id_list .
var_untyped_assigned_decl ::= id_list EQ value_list .


value ::= KW_NULL .
value ::= TOK_STRING . 
value ::= TOK_INT .
value ::= TOK_ID .
value ::= LPARENTHESES value RPARENTHESES .    // (value)
value ::= value PLUS value .                   // value + value
value ::= value MINUS value .                  // value - value
value ::= NOT value .                          // ! value
value ::= value LPARENTHESES value_list RPARENTHESES .  // abc(a, b, c)


value_list ::= value .
value_list ::= value_list COMMA value .
