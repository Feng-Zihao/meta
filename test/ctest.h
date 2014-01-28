

#ifndef CTEST_H
#define CTEST_H

#include <stdio.h>
#include <string.h>

#ifndef CTEST_IGNORE_PASS

#define CASSERT_EQ(actual, expect) \
    if (actual == expect) {\
        printf("\x1B[1;32m[ PASS ]\n\x1B[m");\
    } else { \
        printf("\x1B[1;31m[ FAIL ]  %s:%d\n", __FILE__, __LINE__);\
        printf("actual : %d\n", actual);\
        printf("expect : %d\n", expect);\
        printf("\x1B[m");\
    }

#define CASSERT_STR_EQ(actual, expect) \
    if (strcmp(actual, expect) == 0) {\
        printf("\x1B[1;32m[ PASS ]\n\x1B[m");\
    } else { \
        printf("\x1B[1;31m[ FAIL ]  %s:%d\n", __FILE__, __LINE__);\
        printf("actual : %s\n", actual);\
        printf("expect : %s\n\x1B[m", expect);\
    }

#else

#define CASSERT_EQ(actual, expect) \
    if (actual == expect) {\
    } else { \
        printf("\x1B[1;31m[ FAIL ]  %s:%d\n", __FILE__, __LINE__);\
        printf("actual : %d\n", actual);\
        printf("expect : %d\n", expect);\
        printf("\x1B[m");\
    }

#define CASSERT_STR_EQ(actual, expect) \
    if (strcmp(actual, expect) == 0) {\
    } else { \
        printf("\x1B[1;31m[ FAIL ]  %s:%d\n", __FILE__, __LINE__);\
        printf("actual : %s\n", actual);\
        printf("expect : %s\n\x1B[m", expect);\
    }

#endif


#define CTEST_FUNC(func_name) \
    printf("\x1B[1;35m[ %s ] %s:%d\n\x1B[m", #func_name, __FILE__, __LINE__);\
    func_name();


#endif
