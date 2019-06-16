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
    int i, j;
    char func_name[16];
    unsigned int count_ok, count;
    unsigned int total_ok = 0, total = 0;
    void *handle = NULL;
    void (*set_jump)(jmp_buf *jump);
    jmp_buf fail_jump;

    if (argc <= 1) {
        fprintf(stderr, "usage %s ut*.dll\n", argv[0]);
        return -1;
    }

    for (i = 1; i < argc; i++) {

        fprintf(stderr, "FILE: %s\n", argv[i]);
        handle = dlopen (argv[i], RTLD_LAZY);
        if (handle == NULL) {
            perror("dlopen error");
            continue;
        }
        set_jump = dlsym(handle, "SetJump");
        count_ok = 0;
        count = 0;
        for (j = 0; j < 300; j++) {                     /* MAX NUM TEST */
            sprintf(func_name, "test%03d", j);
            t = (Test) dlsym(handle, func_name);
            if (t != NULL)  {
                count++;
                if (setjmp(fail_jump) == 0) {
                    set_jump(&fail_jump);
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
        printf("%s %u/%u \n", argv[i], count_ok, count);
        total_ok += count_ok;
        total += count;
    }
    printf("TOTAL %u/%u", total_ok, total);

    return 0;
}
