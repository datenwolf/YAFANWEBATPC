#ifndef TESTS_H
#define TESTS_H

#include <stdlib.h>
#include <stdio.h>

#define RET_SUCCESS 0
#define RET_NO_RETURN -12345
#define RET_UNSPEC_ERROR 1

extern const int test_function_count;
extern int (*test_functions[])(int);
extern int tests_run_suite(int argc,char** argv);

//tests
extern int test_dummy(int);
extern int test_space_creator(int);

#endif
