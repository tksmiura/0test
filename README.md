# 0test
Minimal test framework for c

## files

| file           | desc                         |
 ----|----
| LICENSE        |                              |
| README.md	 |				|
| 0test.h	 | main test framework		|
| 0test_cygwin.c | main for cygwin 		|
| Makefile	 | Sample Make file		|
| sample.c	 | Sample Target		|
| ut_sample.c	 | Sample test code		|
| ut_test.c	 | test this framework		|

## Usage

## Example test

### make test

```
$ make test
cc -shared -g -o ut_test.dll ut_test.c
cc -shared -g -o ut_sample.dll ut_sample.c
cc -g -o 0test_cygwin.exe 0test_cygwin.c
./0test_cygwin.exe ut_test.dll ut_sample.dll
FILE: ut_test.dll
    test001 is ok
         ut_test.c:13: 'false' is NOT OK in test002
    test002 is not ok
         check2 'true' is OK
    test003 is ok
ut_test.dll 2/3
FILE: ut_sample.dll
         printf 'strcmp(str, "Hello World\n")==0' is OK
         return value 'ret==0' is OK
    test001 is ok
ut_test.dll 1/1
total 3/4
```

### make test_report

```
$ make test_report
./0test_cygwin.exe ut_test.dll ut_sample.dll 2> /dev/null
ut_test.dll 2/3
ut_test.dll 1/1
total 3/4
```
