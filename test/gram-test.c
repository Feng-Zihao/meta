
#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "gram.h"
#include "ctest.h"


yyscan_t scanner;
YY_BUFFER_STATE buf;
YYSTYPE yystype;
int rs;

void gram_valid_test_struct_decl() {
#define __VALID_STRUCT_DECL(str)\
    yylex_init(&scanner);\
    buf = yy_scan_string(str, scanner);\
    rs = yyparse(scanner);\
    CASSERT_EQ(rs, 0);\
    yy_delete_buffer(buf, scanner);\
    yylex_destroy(scanner);

    const char * args[] = {
        "struct abc {   }",
        "struct abc{}",
        "struct abc {int a}",
        "struct abc {int a = 1}",
        "struct abc {a =\n 1}",
        "struct abc {a<b.c> a = 1, 2,3,3,4}",
        "struct abc {a = b,b,b float b=1}",
        "struct abc {b=all()\nfloat b=1\nint c}"
        "struct abc {b=all(a, Complex(c))\nfloat b=1\nint c}"
    };

    int i;
    for ( i = 0; i < sizeof(args)/sizeof(const char*); i++) {
        __VALID_STRUCT_DECL(args[i]);
    }

}

int main(int argc, const char *argv[])
{

    CTEST_FUNC(gram_valid_test_struct_decl);
    return 0;
}
