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


while_stmt ::= KW_WHILE value statement_block .


if_stmt    ::= KW_IF value statement_block elif_block_list else_block .
elif_block ::= KW_ELIF value statement_block .
elif_block_list ::= .
elif_block_list ::= elif_block .
elif_block_list ::= elif_block_list elif_block .
else_block ::= KW_ELSE statement_block .


assignment_stmt ::= value_list SYM_EQ value_list .   // a, b = c, d
assignment_stmt ::= value_list SYM_EQ value SYM_DIV value .  // a, b = c / d
assignment_stmt ::= value SYM_ADD_EQ value .   // a += b
assignment_stmt ::= value SYM_SUB_EQ value .   // a -= b
assignment_stmt ::= value SYM_MUL_EQ value .   // a *= b
assignment_stmt ::= value SYM_DIV_EQ value .   // a /= b
assignment_stmt ::= value SYM_MOD_EQ value .   // a %= b
assignment_stmt ::= value SYM_POW_EQ value .   // a **= b
assignment_stmt ::= value SYM_SHL_EQ value .   // a <<= b
assignment_stmt ::= value SYM_SHR_EQ value .   // a >>= b
assignment_stmt ::= value SYM_ROL_EQ value .   // a <<<= b
assignment_stmt ::= value SYM_ROR_EQ value .   // a >>>= b
assignment_stmt ::= value SYM_OR_EQ value .    // a ||= b



for_stmt ::= KW_FOR for_stmt_head SYM_SEMICOLON value SYM_SEMICOLON assignment_stmt
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
var_untyped_assigned_decl ::= id_list SYM_EQ value_list .


value ::= KW_NULL .
value ::= TOK_STRING . 
value ::= TOK_INT .
value ::= TOK_ID .
value ::= value SYM_DOT value .
value ::= LPARENTHESES value RPARENTHESES .    // (value)

value ::= value SYM_ADD value .            // value + value
value ::= value SYM_SUB value .            // value - value
value ::= value SYM_MUL value .            // value * value
value ::= value SYM_DIV value .            // value / value
value ::= value SYM_MOD value .            // value % value
value ::= value SYM_POW value .            // value ** value

value ::= value SYM_AND value .            // value && value
value ::= value SYM_OR value .             // value || value
value ::= SYM_NOT value .                  // ! value

/*boolean value*/
value ::= value SYM_EQ value .             // value == value
value ::= value SYM_GT value .             // value > value
value ::= value SYM_LT value .             // value < value
value ::= value SYM_GE value .             // value >= value
value ::= value SYM_LE value .             // value <= value
value ::= value SYM_NE value .             // value != value

/*bitwise operation*/
value ::= value SYM_BIT_AND value .        // value & value
value ::= value SYM_BIT_OR value .         // value | value
value ::= value SYM_BIT_XOR value .        // value ^ value
value ::= value SYM_SHL value .            // value << value
value ::= value SYM_SHR value .            // value >> value
value ::= value SYM_ROL value .            // value <<< value
value ::= value SYM_ROR value .            // value >>> value


value ::= value LPARENTHESES value_list RPARENTHESES .  // abc(a, b, c)


value_list ::= value .
value_list ::= value_list COMMA value .
