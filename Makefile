#
# unit test for cygwin
#
SRCS = sample.c
HEADERS = 0test.h
TEST_SRCS = $(wildcard ut_*.c)
TESTS = $(TEST_SRCS:.c=.dll)
GCOV_TESTS = $(TEST_SRCS:.c=_gcov.dll)

# environment
GCOV ?= gcov

# build targets for test
define MAKETARGETS
$(1): $(1:.dll=.c) $(HEADERS) $(SRCS)
	$(CC) -shared -g -o $(1) $(1:.dll=.c)
endef
$(foreach VAR,$(TESTS),$(eval $(call MAKETARGETS,$(VAR))))

# test runner cygwin
0test_cygwin.exe : 0test_cygwin.c 0test.h
	$(CC) -g -o 0test_cygwin.exe 0test_cygwin.c

.PHONY: test test_report clean

# run tests
test: $(TESTS) 0test_cygwin.exe
	./0test_cygwin.exe $(TESTS)

test_report: $(TESTS) 0test_cygwin.exe
	./0test_cygwin.exe $(TESTS) 2> /dev/null

#
# gcov
#

# target gov (unit test only)
define MAKETARGETS_GCOV
$(1:.c=_gcov.dll): $(1)
	$(CC) $(CFLAGS) -shared -g -o $(1:.c=_gcov.dll) --coverage $(1)
endef
$(foreach VAR,$(TEST_SRCS),$(eval $(call MAKETARGETS_GCOV,$(VAR))))

# run unit tests and gcov
.PHONY: gcov
gcov: $(GCOV_TESTS) 0test_cygwin.exe
	./0test_cygwin.exe $(GCOV_TESTS)
	$(GCOV) -b $(TEST_SRCS:.c=.gcda)

# clean
clean:
	$(RM) ut*.dll 0test_cygwin.exe
