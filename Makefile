#
# unit test
#
SRCS = sample.c
HEADERS = 0test.h
TEST_SRCS = $(wildcard ut_*.c)
TESTS = $(basename $(TEST_SRCS))
GCOV_TESTS = $(TEST_SRCS:.c=_gcov)

# environment
GCOV ?= gcov

# build targets for test
define MAKETARGETS
$(1): $(1).c $(HEADERS) $(SRCS)
	$(CC) -g -o $(1) $(1).c
endef
$(foreach VAR,$(TESTS),$(eval $(call MAKETARGETS,$(VAR))))

.PHONY: test test_report clean

# run tests
.PHONY: test
test: $(TESTS)
	@for test in $(TESTS) ; do \
		echo "test $$test";\
		./$$test ;\
	done

test_report: $(TESTS)
	@for test in $(TESTS) ; do \
		./$$test 2> /dev/null ;\
	done

#
# gcov
#

# target gov (unit test only)
define MAKETARGETS_GCOV
$(1)_gcov: $(1).c
	$(CC) $(CFLAGS) -o $(1)_gcov --coverage $(1).c
endef
$(foreach VAR,$(TESTS),$(eval $(call MAKETARGETS_GCOV,$(VAR))))

# run unit tests and gcov
.PHONY: gcov
gcov: $(GCOV_TESTS)
	@for test in $(GCOV_TESTS) ; do \
		./$$test ;\
	done
	$(GCOV) -b $(TEST_SRCS:.c=.gcda)

# clean
clean:
	$(RM) $(TESTS) $(GCOV_TESTS)
	$(RM) *.gcno *.gcda *.gcov
	$(RM) -r *.dSYM/
