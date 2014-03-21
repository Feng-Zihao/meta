
#include <stdio.h>
#include <stdlib.h>
#include <gtest/gtest.h>
#include "lex.h"
#include "semt.h"
#include "gram.h"


yyscan_t scanner;
YY_BUFFER_STATE buf;
YYSTYPE yystype;
int rs;

TEST(GRAMMAR_TEST, CLASSES) {
#define __VALID_CLASS_DECL(str)\
    yylex_init(&scanner);\
    buf = yy_scan_string(str, scanner);\
    rs = yyparse(scanner);\
    EXPECT_EQ(0, rs);\
    yy_delete_buffer(buf, scanner);\
    yylex_destroy(scanner);

    const char * args[] = {
        "class abc {   }",
        "class abc{}",
        "class abc {int a}",
        "class abc {int a = 1}",
        "class abc {a =\n 1}",
        "class abc{a<b.c> a = 1, 2,3,3,4}",
        "class abc {a<b.c<e.f<g>>> a = 1, 2,3,3,4}",
        "class abc {a = b,b,b float b=1}",
        "class abc{b=all()\nfloat b=1\nint c}",
        "class abc {b=all(a, Complex(c))\nfloat b=1\nint c}"
    };
    int i;
    for ( i = 0; i < sizeof(args)/sizeof(const char*); i++) {
        __VALID_CLASS_DECL(args[i]);
    }
}

TEST(GRAMAR_TEST, FUNCTIONS) {
#define __VALID_FUNC_DECL(str)\
    yylex_init(&scanner);\
    buf = yy_scan_string(str, scanner);\
    rs = yyparse(scanner);\
    EXPECT_EQ(0, rs);\
    yy_delete_buffer(buf, scanner);\
    yylex_destroy(scanner);

    const char * args[] = {
        // test empty decl
        "func a() {}",
        "func a(int a, double b, c){}",
        "func __(int a, b = 1.000, c=Complex(a,b,c)){}",
        "func __(a=1, c<In, ad<b, b>>  b){}",
        "func _a(int a,b,c,d,e,f,g) int, double, Complex<a.b<Complex<c>>> { 1 >>> 3 }",
        "func a(int a,b) { return }",
        "func a(int a,b) { return }",
        "func a(int a,b) { a += 1 b += 2 return a, b, c Complex(d)}",
        "func main(int a, string b) int, double, Complex {\n"
        "   for int i=1;i<size(t);i+=1 {\n"
        "       while next(t) {\n"
        "       }\n"
        "   }\n"
        "   if a < b(t,m) < c < !d {\n"
        "   }\n"
        "   if a < b(t,m) <= c[a < d] < !d {\n"
        "   } elif d > e && b {\n"
        "   }\n"
        "   \n"
        "   return 1<<3"
        "   if (a < b(t,min(c,d,e())) < !!!!c < !d) {\n"
        "   } elif d > e && b {\n"
        "       1 >>> 8 2 <<< 10\n"
        "   } else {\n"
        "   }\n"
        "   a.b.c.d.e.f.g().h.i(i.ao.d, aie.g)\n"
        "   _, _, _, ___ = 1,2,3,4\n"
        "   _, _, _, ___ = Complex(a,b,c,d)\n"
        "   sql.select(abc).where(a>b && b<c)\n"
        "   table_abc[id > 1]\n"
        "   return 0\n"
        "}",
        ""
    };
    int i;
    for ( i = 0; i < sizeof(args)/sizeof(const char*); i++) {
        __VALID_FUNC_DECL(args[i]);
    }
}

int main(int argc, char **argv)
{ 
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
