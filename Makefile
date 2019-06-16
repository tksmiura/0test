
#
# unit test for cygwin
#
HEADERS = 0test.h
TEST_SRCS = $(wildcard ut_*.c)
TESTS = $(TEST_SRCS:.c=.dll)

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
test: $(TESTS) 0test_cygwin.EXE
	./0test_cygwin.exe $(TESTS)

test_report: $(TESTS) 0test_cygwin.exe
	./0test_cygwin.exe $(TESTS) 2> /dev/null

clean:
	$(RM) ut*.dll 0test_cygwin.exe
