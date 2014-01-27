 %{
#include <stdio.h>
#include <assert.h>
#include "lex.h"
#include "gram.h"


void yyerror(void* scanner, const char* msg) {
    fprintf(stderr, "%s\n", msg);
}
%}

%code requires {
#define YYSTYPE char const *
#define YYLEX_PARAM   scanner
void yyerror(void* scanner, const char* msg);
}




/*%define api.pure full*/
%pure-parser
%param {void* scanner}
%expect 0

%left ','
%left "||"
%left "&&"
%left '<' '>' "<=" ">=" "==" "!="
%right '='
%left '+' '-'
%left '*' '/' '%'
%left "**"
%left '&' '|' '^'
%right "<<" ">>" "<<<" ">>>"
%left '.'

%nonassoc '!' "+=" "-=" "*=" "/=" "%=" "**="
%nonassoc "<<=" ">>=" "<<<=" ">>>=" "||="


%token TOK_ID TOK_STRING TOK_INT TOK_FLOAT TOK_NEWLINE
%start prog

%precedence PREC_LOW
%precedence '('

%%
prog :
     %empty
|    prog_block_list ;

prog_block_list:
    prog_block
|   prog_block_list prog_block
;

prog_block :
    struct_decl
|   func_decl
;


struct_decl : "struct" TOK_ID '{' struct_var_decl_list '}';

struct_var_decl_list:
    %empty
|   var_decl
|   struct_var_decl_list TOK_NEWLINE var_decl
;

func_decl : "func" TOK_ID '(' func_arg_decl_list ')' var_type_list statement_block ;


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


while_stmt : "while" expr statement_block ;


if_stmt    :
    if_block else_block
|   if_block elif_block_list else_block
;

if_block : "if" expr statement_block;

elif_block : "elif" expr statement_block ;
elif_block_list :
    elif_block
|   elif_block_list elif_block
;

else_block :
    %empty
|   "else" statement_block
;


assignment_stmt :
    expr_list '=' expr_list
|   expr "+=" expr
|   expr "-=" expr
|   expr "*=" expr
|   expr "/=" expr
|   expr "%=" expr
|   expr "**=" expr
|   expr "<<=" expr
|   expr ">>=" expr
|   expr "<<<=" expr
|   expr ">>>=" expr
|   expr "||=" expr
;



for_stmt : "for" for_stmt_head ';' expr ';' assignment_stmt
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
    "int"
|   "double"
|   "string"
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
    op_expr '(' expr_list ')'
;


indexible_expr:
    op_expr '[' expr_list ']'
;

op_expr:   /* expression that can be used as operand*/
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
    op_expr         %prec PREC_LOW
/*arithmetic expr*/
|   expr '+' op_expr
|   expr '-' op_expr
|   expr '*' op_expr
|   expr '/' op_expr
|   expr '%' op_expr
|   expr "**" op_expr

/*logic arithmetic*/
|   expr "&&" op_expr
|   expr "||" op_expr
|   '!' op_expr

/*comparison op_expr*/
|   expr "==" op_expr
|   expr '>' op_expr
|   expr '<' op_expr
|   expr ">=" op_expr
|   expr "<=" op_expr
|   expr "!=" op_expr

/*bitwise operation*/
|   expr '&' op_expr
|   expr '|' op_expr
|   expr '^' op_expr
|   expr "<<" op_expr
|   expr ">>" op_expr
|   expr "<<<" op_expr
|   expr ">>>" op_expr

;

expr_list :
    expr
|   expr_list ',' expr
;


