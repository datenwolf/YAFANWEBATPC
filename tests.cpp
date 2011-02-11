#define DEFINE_GLOBALS
#include "tests.h"
int tests_run_suite(int argc,char** argv){
  int idx;
  int tmp=RET_NO_RETURN;
  for(idx=0;idx<test_function_count;idx++){
    tmp=test_functions[idx](tmp);
  }
  return tmp;
}
