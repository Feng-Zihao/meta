
#include <stdlib.h>
#include <stdio.h>
#include "def.h"
#include "lex.h"

int main(int argc, const char *argv[])
{
    yyscan_t scanner;
    yylex_init(&scanner);
    yylex_destroy(scanner);
    printf("hello");
    return 0;
}
