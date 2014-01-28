 %{
#include <stdio.h>
#include <assert.h>
#include "gram.h"

#define YY_HEADER_EXPORT_START_CONDITIONS
#include "lex.h"

void yyerror(void* scanner, const char* msg) {
    fprintf(stderr, "%s\n", msg);
}


%}

%code requires {
void yyerror(void* scanner, const char* msg);
}




/*%define api.pure full*/
%pure-parser
%param {void* scanner}
%expect 0

%left ','
%left OP_LOGIC_OR
%left OP_LOGIC_AND
%left '<' '>' OP_LE OP_GE OP_CMP_EQ OP_NE
%right '='
%left '+' '-'
%left '*' '/' '%'
%left OP_POW
%left '&' '|' '^'
%right OP_SHL OP_SHR OP_ROL OP_ROR
%left '.'

%nonassoc '!' OP_ADD_EQ OP_SUB_EQ OP_MUL_EQ OP_DIV_EQ OP_MOD_EQ OP_POW_EQ
%nonassoc OP_SHL_EQ OP_SHR_EQ OP_ROL_EQ OP_ROR_EQ OP_OR_EQ


%token TOK_ID TOK_STRING TOK_INT TOK_FLOAT TOK_NEWLINE
%token KW_STRUCT KW_FUNC KW_WHILE KW_FOR KW_IF KW_ELIF KW_ELSE KW_INT KW_FLOAT KW_STRING
%token OP_SHR_EQ OP_SHL_EQ OP_ROR_EQ OP_ROL_EQ OP_OR_EQ OP_ADD_EQ
%token OP_SUB_EQ OP_MUL_EQ OP_DIV_EQ OP_MOD_EQ OP_POW_EQ
%token OP_SHR OP_SHL OP_ROR OP_ROL OP_POW
%token OP_LOGIC_AND OP_LOGIC_OR
%token OP_CMP_EQ OP_GE OP_LE OP_NE


%start prog
%precedence PREC_LOW
%precedence '('


%%
prog :
    %empty
|   prog_block_list
;

prog_block_list:
    prog_block
|   prog_block_list prog_block
;

prog_block :
    struct_decl
|   func_decl
;


struct_decl : KW_STRUCT TOK_ID '{' struct_var_decl_list '}';

struct_var_decl_list:
    /*%empty*/
    var_decl
|   struct_var_decl_list {yy_push_state(FORCE_NEWLINE, scanner);}
        TOK_NEWLINE {yy_pop_state(scanner);}
        var_decl
;

func_decl : KW_FUNC TOK_ID '(' func_arg_decl_list ')' var_type_list statement_block ;


func_arg_decl:
    TOK_ID '=' expr
|   var_type TOK_ID
|   TOK_ID
;


func_arg_decl_list:
    %empty
|   func_arg_decl
|   func_arg_decl_list ',' func_arg_decl
;


statement_block :
    '{' '}'
|   '{' statement_list '}'
;


statement_list :
    statement
|   statement_list statement
;


statement : 
    for_stmt
|   while_stmt
|   if_stmt
|   assignment_stmt
|   expr
;


while_stmt : KW_WHILE expr statement_block ;


if_stmt :
   if_block elif_block_list else_block
;

if_block : KW_IF expr statement_block;

elif_block : KW_ELIF expr statement_block ;
elif_block_list :
    elif_block
|   elif_block_list elif_block
;

else_block :
    %empty
|   KW_ELSE statement_block
;


assignment_stmt :
    expr_list '=' expr_list
|   expr OP_ADD_EQ expr         /* a += b   */
|   expr OP_SUB_EQ expr         /* a -= b   */
|   expr OP_MUL_EQ expr         /* a *= b   */
|   expr OP_DIV_EQ expr         /* a /= b   */
|   expr OP_MOD_EQ expr         /* a %= b   */
|   expr OP_POW_EQ expr         /* a *= b   */
|   expr OP_SHL_EQ expr         /* a <<= b  */
|   expr OP_SHR_EQ expr         /* a >>= b  */
|   expr OP_ROL_EQ expr         /* a <<<= b */
|   expr OP_ROR_EQ expr         /* a >>>= b */
|   expr OP_OR_EQ expr          /* a ||= b  */
;



for_stmt : KW_FOR for_stmt_head ';' expr ';' assignment_stmt
             statement_block;
for_stmt_head :
    %empty
|   var_typed_assigned_decl
|   var_untyped_assigned_decl
;


id_chain : // aa.bb.cc.dd
    TOK_ID
|   id_chain '.' TOK_ID
;


id_list : // aa, bb, cc, dd
    TOK_ID
|   id_list ',' TOK_ID
;


var_decl :
    var_typed_assigned_decl
|   var_untyped_assigned_decl
|   var_typed_unassigned_decl
;


primitive_var_type:
    KW_INT
|   KW_FLOAT
|   KW_STRING
;


var_type :
    primitive_var_type
|   id_chain
|   var_type '<' var_type_list '>'
;

var_type_list :
    var_type
|   var_type_list ',' var_type
;

var_typed_assigned_decl : var_typed_unassigned_decl '=' expr_list;
var_typed_unassigned_decl : var_type id_list ;
var_untyped_assigned_decl : id_list '=' expr_list ;


const_token_expr:
    "null"
|   TOK_STRING
|   TOK_INT
|   TOK_FLOAT
;


fcall_expr:
    operand '(' expr_list ')'
;


indexible_expr:
    operand '[' expr_list ']'
;

operand:   /* expression that can be used as operand*/
    const_token_expr
|   id_chain
|   TOK_INT '.' id_chain
|   TOK_STRING '.' id_chain
|   '(' expr ')'
|   fcall_expr
|   fcall_expr '.' id_chain
|   indexible_expr
|   indexible_expr '.' id_chain
;


expr :
    operand         %prec PREC_LOW
/*arithmetic expr*/
|   expr '+' operand
|   expr '-' operand
|   expr '*' operand
|   expr '/' operand
|   expr '%' operand
|   expr OP_POW operand

/*logic arithmetic*/
|   expr OP_LOGIC_AND operand   /* a && b */
|   expr OP_LOGIC_OR  operand   /* a || b */
|   '!' operand

/*comparison operand*/
|   expr OP_CMP_EQ operand  /* a == b */
|   expr '>' operand
|   expr '<' operand
|   expr OP_GE operand      /* a >= b */
|   expr OP_LE operand      /* a <= b */
|   expr OP_NE operand      /* a != b */

/*bitwise operation*/
|   expr '&' operand
|   expr '|' operand
|   expr '^' operand
|   expr OP_SHL operand     /* a << b */
|   expr OP_SHR operand     /* a >> b */
|   expr OP_ROL operand     /* a <<< b */
|   expr OP_ROR operand     /* a >>> b */

;

expr_list :
    expr
|   expr_list ',' expr
;


