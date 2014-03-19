

#ifndef SEMT_H
#define SEMT_H

#include <sys/queue.h>
#include <stdlib.h>
#include <stdio.h>


#define ARRAY_INIT_DEFAULT_SIZE 10


typedef struct YYLTYPE {
    /* defaults */
    int first_line;
    int first_column;
    int last_line;
    int last_column;
    /*  added */
    FILE* file;
    struct class_decl** class_decls;
    size_t calss_size;
} YYLTYPE;

typedef union YYSTYPE {

} YYSTYPE;


typedef struct class_decl {
    char* class_name;
    struct var_decl* members;
} class_decl_t;


typedef struct var_decl {
    int type;
    char** ids;
    size_t id_size;
    struct expr** exprs;
    size_t expr_size;
} var_decl_t;


typedef struct expr {
    int operator_type;
    struct expr* op[2];
    /* self node data */
    int operand_type;
    
} expr_t;


typedef struct operand_expr {
    struct basic_expr** attrs;
    size_t size;

    struct expr** arguments;  // NULL for attributes only
                              // NONNULL for callable or indexible
    
    int type;                 // clalable or indexible, or not operator
    struct operand_expr* next;
} operand_expr_t;


typedef struct basic_expr {
    int type;
    char* text;
} basic_expr_t;

#endif
