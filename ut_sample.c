#include <string.h>
#include "0test.h"

/* if exist main in target code */
#define main original_main

/* stub functons */
#define printf stub_printf

/* stub code */
int stub_printf(const char* str)
{
    TEST_ASSERT("printf", strcmp(str, "Hello World\n")==0);

    return 0;
}

/* test target */
#include "sample.c"


bool test001(void)
{
    int c = 1;
    char* arg[] = {"sample"};
    int ret;

    ret = main(c, arg);

    TEST_ASSERT("return value", ret==0);

    return true;
}
