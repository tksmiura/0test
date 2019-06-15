#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <setjmp.h>
#include <dlfcn.h>
#include "0test.h"

jmp_buf FailJump;


int main(int argc, char *argv[])
{
    Test t;
    bool ret;
    int i;
    char func_name[16];
    unsigned int count_ok = 0, count = 0;
    void *handle = NULL;
    void (*set_jump)(jmp_buf *jump);
    jmp_buf fail_jump;

    if (argc <= 1) {
        fprintf(stderr, "usage %s <-c> ut*.dll\n", argv[0]);
        return -1;
    }

    handle = dlopen (argv[1], RTLD_LAZY);
    if (handle == NULL) {
        perror("dlopen error");
        return -1;
    }
    set_jump = dlsym(handle, "SetJump");
    for (i = 0; i < 100; i++) {
        sprintf(func_name, "test%03d", i);
        t = (Test) dlsym(handle, func_name);
        if (t != NULL)  {
            count++;
            if (setjmp(fail_jump) == 0) {
                set_jump(&fail_jump);
                ret = (*t)();
            } else
                ret = false;

            if (ret)
                count_ok++;
            else
                fprintf(stderr, "test FAILURE in %s\n", func_name);
        }
    }
    printf("%s %u/%u \n", argv[1], count_ok, count);

    return 0;
}
