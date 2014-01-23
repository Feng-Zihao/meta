

#ifndef CTEST_H
#define CTEST_H

#include <stdio.h>
#include <string.h>



#ifndef CTEST_IGNORE_PASS
#define CASSERT(value) \
    if (value) {\
        printf("\x1B[1;32m[ PASS ]\n\x1B[m");\
    } else { \
        printf("\x1B[1;31m[ FAIL ]  %s:%d\n\x1B[m", __FILE__, __LINE__);\
    }
#else
#define CASSERT(value) \
    if (value) {\
    } else { \
        printf("\x1B[1;31m[ FAIL ]  %s:%d\n\x1B[m", __FILE__, __LINE__);\
    }

#endif



#define CASSERT_EQ(actual, expect) CASSERT(actual == expect)
#define CASSERT_STR_EQ(actual, expect) CASSERT(strcmp(actual, expect) == 0)

#define CTEST_FUNC(func_name) \
    printf("\x1B[1;35m[ %s ] %s:%d\n\x1B[m", #func_name, __FILE__, __LINE__);\
    func_name();


#endif
