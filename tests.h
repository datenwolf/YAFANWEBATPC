#ifndef TESTS_H
#define TESTS_H

#include <stdlib.h>
#include <stdio.h>

#define RET_SUCCESS 0
#define RET_NO_RETURN -12345
#define RET_UNSPEC_ERROR 1

//UGLY HACK!!!!!!!
#ifdef DEFINE_GLOBALS
int test_dummy(int x) { printf("TEST DUMMY: %i\n",x); return x; };
const int test_function_count=1;
int (*test_functions[test_function_count])(int) = {&test_dummy};
int tests_run_suite(int argc,char** argv);
#else
extern int test_dummy(int x);
extern const int test_function_count;
extern int (*test_functions[])(int);
extern int tests_run_suite(int argc,char** argv);
#endif

#endif
