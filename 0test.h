/*
 *  0 Test - minimal test framework for C
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <setjmp.h>
#include <dlfcn.h>

/* macro for test code in target source */
#define __UNIT_TEST__ 1

/* test assert */
#define TEST_ASSERT(s, f) \
    { \
    if (f) {                                                            \
        fprintf(stderr, s " '%s' is OK\n",#f);                          \
    } else {                                                            \
        fprintf(stderr, "%s:%u: '%s' is FAILURE in %s\n",               \
               __FILE__,__LINE__,#f,__func__);                          \
        longjmp(FailJump, 1);                                           \
    }}

extern jmp_buf FailJump;

/* test function prototype */
typedef bool (*Test)(void);

#ifndef __CYGWIN__
int main(int argc, char *argv[])
{
    Test t;
    bool ret;
    int i;
    char func_name[100];
    unsigned int count_ok = 0, count = 0;

    memset(func_name, 0, sizeof(func_name));
    for (i = 0; i < 100; i++) {
        sprintf(func_name, "test%03d", i);
        t = (Test) dlsym(RTLD_DEFAULT, func_name);
        if (t != NULL)  {
            count++;
            ret = (*t)();
            if (ret)
                count_ok++;
            else
                printf("test NG %s\n", func_name);
        }
    }
    printf("result %u/%u \n", count_ok, count);
}
#else
jmp_buf FailJump;

void SetJump(jmp_buf* jump)
{
    memcpy(&FailJump, jump, sizeof(jmp_buf));
}
#endif
