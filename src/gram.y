 %{
    #include <stdio.h>
    #include <assert.h>
    #include "def.h"
    #define YYSTYPE char const *
%}


/*%define api.pure full*/
%pure-parser

%left "||"
%left "&&"

%left '+' '-'
%left '*' '/'
%left "**"
%left '.'
%nonassoc '!'

%token TOK_ID TOK_STRING TOK_INT TOK_FLOAT
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


struct_decl : "struct" TOK_ID '{' var_decl_list '}';


func_decl : "func" TOK_ID '(' var_decl_list ')' var_type_list statement_block ;


statement_block : '{' statement_list '}';


statement_list :
    %empty
|   statement
|   statement_list statement
;


statement : 
    for_stmt
|   while_stmt
|   if_stmt
|   assignment_stmt
;


while_stmt : "while" expr statement_block ;


if_stmt    : "if" expr statement_block elif_block_list else_block ;
elif_block : "elif" expr statement_block ;
else_block :
    %empty
|   "else" statement_block
;


elif_block_list :
    %empty
|   elif_block
|   elif_block_list elif_block
|   "else" statement_block
;


assignment_stmt :
    expr_list '=' expr_list
|   expr_list '=' expr '/' expr
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


var_decl_list : 
    %empty
|   var_decl
|   var_decl_list var_decl
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


expr :
    "null"
|   TOK_STRING
|   TOK_INT
|   TOK_ID
|   TOK_FLOAT
|   expr '.' expr
|   '(' expr ')'

|   expr '+' expr            // expr + expr
|   expr '-' expr            // expr - expr
|   expr '*' expr            // expr * expr
|   expr '/' expr            // expr / expr
|   expr '%' expr            // expr % expr
|   expr "**" expr            // expr ** expr

|   expr "&&" expr            // expr && expr
|   expr "||" expr             // expr || expr
|   '!' expr                  // ! expr

/*boolean expr*/
|   expr "==" expr              // expr == expr
|   expr '>' expr              // expr > expr
|   expr '<' expr              // expr < expr
|   expr ">=" expr              // expr >= expr
|   expr "<=" expr              // expr <= expr
|   expr "!=" expr              // expr != expr

/*bitwise operation*/
|   expr '&' expr         // expr & expr
|   expr '|' expr          // expr | expr
|   expr '^' expr         // expr ^ expr
|   expr "<<" expr             // expr << expr
|   expr ">>" expr             // expr >> expr
|   expr "<<<" expr             // expr <<< expr
|   expr ">>>" expr             // expr >>> expr


|   expr '(' expr_list ')'
;


expr_list :
    expr
|   expr_list ',' expr
;
