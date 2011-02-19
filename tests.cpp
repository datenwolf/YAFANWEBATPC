#include "tests.h"
#include "space_creator.h"


const int test_function_count=3;
int (*test_functions[test_function_count])(int) = {&test_dummy,&test_space_creator,&test_dummy};

int tests_run_suite(int* argc,char** argv){
  int idx;
  int tmp=RET_NO_RETURN;
  for(idx=0;idx<test_function_count;idx++){
    tmp=test_functions[idx](tmp);
  }
  return tmp;
}


//tests
int test_dummy(int x) {
  printf("TEST DUMMY: %i\n",x);
  return x;
};

int test_space_creator(int x) {
  printf("TEST space creator\n");
  std::vector<space_object> vtest1;
  std::vector<space_object> vtest2;
  vtest2=space_create_tree(vtest1,(unsigned int)0,true);
  space_object test2=vtest2[0];
  printf("VTEST2[0]:\n");
  printf("  id:      %i\n",test2.id);
  printf("  parent:  %i\n",test2.parent);
  printf("  x:       %f\n",test2.x);
  printf("  y:       %f\n",test2.y);
  printf("  z:       %f\n",test2.z);
  printf("  rotx:    %i\n",test2.rotx);
  printf("  roty:    %i\n",test2.roty);
  printf("  rotz:    %i\n",test2.rotz);
  printf("  model:   %s\n",test2.model);
  printf("  texname: %s\n",test2.texname);
  return 0;
}
