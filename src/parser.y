%include {
#include <stdio.h>
#include <assert.h>
#include "parser.h"
#include "def.h"
}

%token_type {const char*}

%syntax_error {
    fprintf(stderr, "Error parsing command\n");
}

%name Meta
%start_symbol prog

/*%left COMMA DOT .*/
%left SYM_OR .
%left SYM_AND .

%left SYM_ADD SYM_SUB .
%left SYM_MUL SYM_DIV .
%left SYM_POW .
%left SYM_DOT .
%nonassoc SYM_NOT .


prog ::= prog_block .
prog_block ::= prog_block prog_block .
prog_block ::= struct_decl .
prog_block ::= func_decl .
prog_block ::= .


struct_decl ::= KW_STRUCT TOK_ID SYM_LBRACE var_decl_list SYM_RBRACE .


func_decl ::= KW_FUNC TOK_ID LPARENTHESES var_decl_list 
              RPARENTHESES var_type_list statement_block .


statement_block ::= SYM_LBRACE statement_list SYM_RBRACE .


statement_list ::= .
statement_list ::= statement .
statement_list ::= statement_list statement .


/*statement ::= for_stmt .*/
statement ::= while_stmt .
statement ::= if_stmt .
statement ::= for_stmt .
statement ::= assignment_stmt .


while_stmt ::= KW_WHILE expr statement_block .


if_stmt    ::= KW_IF expr statement_block elif_block_list else_block .
elif_block ::= KW_ELIF expr statement_block .
elif_block_list ::= .
elif_block_list ::= elif_block .
elif_block_list ::= elif_block_list elif_block .
else_block ::= KW_ELSE statement_block .


assignment_stmt ::= expr_list SYM_EQ expr_list .   // a, b = c, d
assignment_stmt ::= expr_list SYM_EQ expr SYM_DIV expr .  // a, b = c / d
assignment_stmt ::= expr SYM_ADD_EQ expr .   // a += b
assignment_stmt ::= expr SYM_SUB_EQ expr .   // a -= b
assignment_stmt ::= expr SYM_MUL_EQ expr .   // a *= b
assignment_stmt ::= expr SYM_DIV_EQ expr .   // a /= b
assignment_stmt ::= expr SYM_MOD_EQ expr .   // a %= b
assignment_stmt ::= expr SYM_POW_EQ expr .   // a **= b
assignment_stmt ::= expr SYM_SHL_EQ expr .   // a <<= b
assignment_stmt ::= expr SYM_SHR_EQ expr .   // a >>= b
assignment_stmt ::= expr SYM_ROL_EQ expr .   // a <<<= b
assignment_stmt ::= expr SYM_ROR_EQ expr .   // a >>>= b
assignment_stmt ::= expr SYM_OR_EQ expr .    // a ||= b



for_stmt ::= KW_FOR for_stmt_head SYM_SEMICOLON expr SYM_SEMICOLON assignment_stmt
             statement_block .
for_stmt_head ::= var_typed_assigned_decl .
for_stmt_head ::= var_untyped_assigned_decl .
for_stmt_head ::= .


var_decl_list ::= .
var_decl_list ::= var_decl .
var_decl_list ::= var_decl_list var_decl .


id_chain ::= TOK_ID .                      // aa.bb.cc.dd
id_chain ::= id_chain SYM_DOT TOK_ID .


id_list ::= TOK_ID .                       // aa, bb, cc, dd
id_list ::= id_list SYM_COMMA TOK_ID .


var_decl ::= var_typed_assigned_decl .
var_decl ::= var_untyped_assigned_decl .
var_decl ::= var_typed_unassigned_decl .


primitive_var_type ::= KW_INT .
primitive_var_type ::= KW_DOUBLE .
primitive_var_type ::= KW_STRING .


var_type ::= primitive_var_type .
var_type ::= id_chain .   // xxx  xxx.xxx
var_type ::= var_type SYM_LBRACKET var_type_list SYM_RBRACKET .  // type_tmpl< type >
var_type_list ::= var_type .
var_type_list ::= var_type_list COMMA var_type .


var_typed_assigned_decl ::= var_type var_untyped_assigned_decl .
var_typed_unassigned_decl ::= var_type id_list .
var_untyped_assigned_decl ::= id_list SYM_EQ expr_list .


expr ::= KW_NULL .
expr ::= TOK_STRING . 
expr ::= TOK_INT .
expr ::= TOK_ID .
expr ::= TOK_FLOAT .
expr ::= expr SYM_DOT expr .
expr ::= LPARENTHESES expr RPARENTHESES .    // (expr)

expr ::= expr SYM_ADD expr .            // expr + expr
expr ::= expr SYM_SUB expr .            // expr - expr
expr ::= expr SYM_MUL expr .            // expr * expr
expr ::= expr SYM_DIV expr .            // expr / expr
expr ::= expr SYM_MOD expr .            // expr % expr
expr ::= expr SYM_POW expr .            // expr ** expr

expr ::= expr SYM_AND expr .            // expr && expr
expr ::= expr SYM_OR expr .             // expr || expr
expr ::= SYM_NOT expr .                  // ! expr

/*boolean expr*/
expr ::= expr SYM_EQ expr .             // expr == expr
expr ::= expr SYM_GT expr .             // expr > expr
expr ::= expr SYM_LT expr .             // expr < expr
expr ::= expr SYM_GE expr .             // expr >= expr
expr ::= expr SYM_LE expr .             // expr <= expr
expr ::= expr SYM_NE expr .             // expr != expr

/*bitwise operation*/
expr ::= expr SYM_BIT_AND expr .        // expr & expr
expr ::= expr SYM_BIT_OR expr .         // expr | expr
expr ::= expr SYM_BIT_XOR expr .        // expr ^ expr
expr ::= expr SYM_SHL expr .            // expr << expr
expr ::= expr SYM_SHR expr .            // expr >> expr
expr ::= expr SYM_ROL expr .            // expr <<< expr
expr ::= expr SYM_ROR expr .            // expr >>> expr


expr ::= expr LPARENTHESES expr_list RPARENTHESES .  // abc(a, b, c)


expr_list ::= expr .
expr_list ::= expr_list COMMA expr .
