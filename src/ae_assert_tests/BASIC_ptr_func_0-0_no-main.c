#include "stdbool.h"
extern void svf_assert(bool);
void swap(char **p, char **q){
  char* t = *p; 
       *p = *q; 
       *q = t;
      svf_assert(*q == t);
}
int no_main_BASIC_ptr_func_0_0(){
      char a1, b1; 
      char *a = &a1;
      char *b = &b1;
      swap(&a,&b);  
}