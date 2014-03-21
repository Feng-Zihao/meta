

#ifndef SEMT_H
#define SEMT_H

#include <sys/queue.h>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <vector>


using namespace std;


#define ARRAY_INIT_DEFAULT_SIZE 10

class Expr;

class VarDecl {
public:
    int type;
    vector<string> ids;
    vector<Expr> exprs;
};



class ClassDecl {
public:
    string name;
    vector<VarDecl> members;
};


class BasicExpr {
public:
    int type;
    string text;
};


class OperandExpr {
public:
    vector<BasicExpr*> attrs;

    vector<Expr*> arguments;  // NULL for attributes only
                              // NONNULL for callable or indexible
    
    int type;                 // clalable or indexible, or not operator
    OperandExpr* next;
};

class Expr {
public:
    int operator_type;
    Expr* op[2];
    /* self node data */
    int operand_type;
    
};




class YYLTYPE {
public:
    /* defaults */
    int first_line;
    int first_column;
    int last_line;
    int last_column;
    /*  added */
    FILE* file;
    vector<ClassDecl*> classDecls;
};

union YYSTYPE {

};



#endif
