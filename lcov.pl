#!/usr/bin/perl

open(FILE, "lcov -c -d . --rc lcov_branch_coverage=1|") || die "can not run lcov\n";

$out = 1;
while ($line = <FILE>) {
    #SF:/home/miura/dev/0test/0test.h
    if ($line =~ /^SF:.*\/0test\.h/ ||
        $line =~ /^SF:.*\/0test_cygwin\.c/ ||
        $line =~ /^SF:.*\/ut_.*\.c/) {
        $out = 0;
    }
    if ($out) {
        print $line;
    }
    if ($line =~/^end_of_record/) {
        $out = 1;
    }
}
