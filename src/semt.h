

#ifndef SEMT_H
#define SEMT_H

#include <sys/queue.h>
#include <stdlib.h>
#include "lex.h"
#include "gram.h"


#define ARRAY_INIT_DEFAULT_SIZE 10


typedef struct class_decl {
    char* class_name;
    struct var_decl* members;
} class_decl_t;


typedef struct var_decl {
    int type;
    char** ids;
    struct expr** exprs;
} var_decl_t;

typedef struct expr {
    int operator_type;
    struct expr* op[2];
    /* self node data */
    int operand_type;
    
} expr_t;

typedef struct operand_expr {
    
} operand_expr_t;

typedef struct callable_indexible_expr {
    int type; // callable or indexible
    struct operand_expr* operand;
    struct expr** arguments;
    size_t size;
} callable_indexible_expr_t;;

#endif
