
#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "gram.h"
#include "ctest.h"

int main(int argc, const char *argv[])
{

    yyscan_t scanner;
    YY_BUFFER_STATE buf;
    YYSTYPE yystype;
    

    yylex_init(&scanner);

    buf = yy_scan_string("\n", scanner);

    CASSERT_EQ(yyparse(scanner), 0);

    yy_delete_buffer(buf, scanner);
    yylex_destroy(scanner);

    return 0;
}
