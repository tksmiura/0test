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
        fprintf(stderr, "         %s '%s' is OK\n", s, #f);             \
    } else {                                                            \
        fprintf(stderr, "         %s:%u: '%s' is NOT OK in %s\n",       \
               __FILE__, __LINE__, #f, __func__);                       \
        longjmp(FailJump, 1);                                           \
    }}

extern jmp_buf FailJump;

/* test function prototype */
typedef bool (*Test)(void);

#ifndef __CYGWIN__
/* mac or linux */
jmp_buf FailJump;

int main(int argc, char *argv[])
{
    Test t;
    bool ret;
    int j;
    char func_name[16];
    unsigned int count_ok, count;

    fprintf(stderr, "FILE: %s\n", argv[0]);
    count_ok = 0;
    count = 0;
    for (j = 0; j < 300; j++) {                     /* MAX NUM TEST */
        sprintf(func_name, "test%03d", j);
        t = (Test) dlsym(RTLD_DEFAULT, func_name);
        if (t != NULL)  {
            count++;
            if (setjmp(FailJump) == 0) {
                ret = (*t)();
            } else
                ret = false;

            if (ret) {
                fprintf(stderr, "    %s is ok\n", func_name);
                count_ok++;
            } else
                fprintf(stderr, "    %s is not ok\n", func_name);
        }
    }
    printf("%s %u/%u \n", argv[0], count_ok, count);

    return 0;
}
#else
jmp_buf FailJump;

void SetJump(jmp_buf* jump)
{
    memcpy(&FailJump, jump, sizeof(jmp_buf));
}
#endif
