 %{
    #include <stdio.h>
    #include <assert.h>
    #include "def.h"
    #define YYSTYPE char const *
%}


/*%define api.pure full*/
%pure-parser

%left ','
%left "||"
%left "&&"
%left '<' '>' "<=" ">=" "==" "!="
%left '+' '-'
%left '*' '/'
%left '&' '|' '^'
%left "**"
%left '%'
%right "<<" ">>" "<<<" ">>>"
%right '='
%left '.'

%nonassoc '!' "+=" "-=" "*=" "/=" "%=" "**="
%nonassoc "<<=" ">>=" "<<<=" ">>>=" "||="


%left PREC_1
%left PREC_9


%token TOK_ID TOK_STRING TOK_INT TOK_FLOAT TOK_NEWLINE
%start prog

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
    TOK_ID '=' expr   %prec PREC_9
|   var_type id_list  %prec PREC_1
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
|   id_chain '.' TOK_ID     %prec PREC_9
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


expr :
/*basic value*/
   "null"
|   TOK_STRING
|   TOK_INT
|   TOK_FLOAT
|   id_chain      %prec PREC_1
|   '(' expr ')'

/*arithmetic expr*/
|   expr '+' expr
|   expr '-' expr
|   expr '*' expr
|   expr '/' expr
|   expr '%' expr
|   expr "**" expr

/*logic arithmetic*/
|   expr "&&" expr
|   expr "||" expr
|   '!' expr

/*comparison expr*/
|   expr "==" expr
|   expr '>' expr
|   expr '<' expr
|   expr ">=" expr
|   expr "<=" expr
|   expr "!=" expr

/*bitwise operation*/
|   expr '&' expr
|   expr '|' expr
|   expr '^' expr
|   expr "<<" expr
|   expr ">>" expr
|   expr "<<<" expr
|   expr ">>>" expr
|   expr '.' id_chain '(' expr_list ')'
|   expr '.' id_chain '(' ')'
;


expr_list :
    expr
|   expr_list ',' expr
;
