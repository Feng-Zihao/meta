 %{
#include <stdio.h>
#include <assert.h>
#include "gram.h"
#include "lex.h"
#include "semt.h"

void yyerror(YYLTYPE *llocp, yyscan_t scanner,
             const char* msg)
{
    fprintf(stderr, "%s\n", msg);
    fprintf(stderr, "locations %d:%d\n",
            llocp->first_line, llocp->first_column);
}


%}

/*%define api.pure full*/
%pure-parser
%locations
%param {void* scanner}
%expect 0

%precedence PREC_LOW

%left ','
%left OP_LOGIC_OR
%left OP_LOGIC_AND
%left '<' '>' OP_LE OP_GE OP_CMP_EQ OP_NE
%left '+' '-'
%left '*' '/' '%'
%left OP_POW
%left '&' '|' '^'
%right OP_SHL OP_SHR OP_ROL OP_ROR
%right '!'
%left '.'

%nonassoc '='
%nonassoc OP_ADD_EQ OP_SUB_EQ OP_MUL_EQ OP_DIV_EQ OP_MOD_EQ OP_POW_EQ
%nonassoc OP_SHL_EQ OP_SHR_EQ OP_ROL_EQ OP_ROR_EQ OP_OR_EQ


%token TOK_ID TOK_STRING TOK_INT TOK_FLOAT
%token KW_CLASS KW_FUNC KW_WHILE KW_FOR KW_IF KW_ELIF KW_ELSE KW_INT KW_FLOAT KW_STRING KW_RETURN KW_NULL
%token OP_SHR_EQ OP_SHL_EQ OP_ROR_EQ OP_ROL_EQ OP_OR_EQ OP_ADD_EQ
%token OP_SUB_EQ OP_MUL_EQ OP_DIV_EQ OP_MOD_EQ OP_POW_EQ
%token OP_SHR OP_SHL OP_ROR OP_ROL OP_POW
%token OP_LOGIC_AND OP_LOGIC_OR
%token OP_CMP_EQ OP_GE OP_LE OP_NE


%start prog


%precedence '(' '['
%precedence TOK_ID
%precedence TOK_STRING
%precedence TOK_INT
%precedence TOK_FLOAT
%precedence KW_NULL


/* for terminals */
%union {
};

%code requires {

#define YYLTYPE_IS_DECLARED
typedef struct YYLTYPE {
    /* defaults */
    int first_line;
    int first_column;
    int last_line;
    int last_column;
    /*  added */
    FILE* file;
    struct class_decl** class_decls;
} YYLTYPE;

}



%%
prog :
    %empty
|   prog_block_list
;

prog_block_list :
    prog_block
|   prog_block_list prog_block
;

prog_block :
    class_decl
|   func_decl
;


class_decl : KW_CLASS TOK_ID class_decl_body;

class_decl_body : 
    '{' '}'
|   '{' class_member_decl_list '}'

class_member_decl_list:
    var_decl 
|   class_member_decl_list var_decl
;

func_decl :
    KW_FUNC TOK_ID '(' func_arg_decl_list ')' var_type_list statement_block 
|   KW_FUNC TOK_ID '(' func_arg_decl_list ')' statement_block ;


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
|   return_stmt
|   assignment_stmt
|   expr
;


while_stmt : KW_WHILE expr statement_block ;


if_stmt :
   if_block elif_block_list else_block
|  if_block else_block
;

if_block : KW_IF expr statement_block;

elif_block : KW_ELIF expr statement_block;
elif_block_list :
    elif_block
|   elif_block_list elif_block
;

else_block :
    %empty
|   KW_ELSE statement_block
;


return_stmt :
    KW_RETURN       %prec PREC_LOW
|   KW_RETURN expr_list
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
|   var_type '<' {yy_push_state(ACCEPT_RIGHT_ANGLE_BRACKET, scanner);}
        var_type_list
    '>' {yy_pop_state(scanner);}
;

var_type_list :
    var_type
|   var_type_list ',' var_type
;

var_typed_assigned_decl : var_typed_unassigned_decl '=' expr_list ;
var_typed_unassigned_decl : var_type id_list ;
var_untyped_assigned_decl : id_list '=' expr_list ;


const_token_expr:
    KW_NULL
|   TOK_STRING
|   TOK_INT
|   TOK_FLOAT
;


callable_indexible_expr:
    operand_expr '(' ')'
|   operand_expr '(' expr_list ')'
|   operand_expr '[' expr_list ']'
;

operand_expr:   /* expression that can be used as operand_expr*/
    const_token_expr
|   id_chain
|   '(' expr ')'
|   '!' operand_expr
|   callable_indexible_expr
|   TOK_INT '.' id_chain
|   TOK_STRING '.' id_chain
|   callable_indexible_expr '.' id_chain   /* attribute access */
;


expr :
    operand_expr         %prec PREC_LOW
/*arithmetic expr*/
|   expr '+' operand_expr
|   expr '-' operand_expr
|   expr '*' operand_expr
|   expr '/' operand_expr
|   expr '%' operand_expr
|   expr OP_POW operand_expr

/*logic arithmetic*/
|   expr OP_LOGIC_AND operand_expr   /* a && b */
|   expr OP_LOGIC_OR  operand_expr   /* a || b */

/*comparison operand_expr*/
|   expr OP_CMP_EQ operand_expr  /* a == b */
|   expr '>' operand_expr
|   expr '<' operand_expr
|   expr OP_GE operand_expr      /* a >= b */
|   expr OP_LE operand_expr      /* a <= b */
|   expr OP_NE operand_expr      /* a != b */

/*bitwise operation*/
|   expr '&' operand_expr
|   expr '|' operand_expr
|   expr '^' operand_expr
|   expr OP_SHL operand_expr     /* a << b */
|   expr OP_SHR operand_expr     /* a >> b */
|   expr OP_ROL operand_expr     /* a <<< b */
|   expr OP_ROR operand_expr     /* a >>> b */
;

expr_list :
    expr
|   expr_list ',' expr
;


