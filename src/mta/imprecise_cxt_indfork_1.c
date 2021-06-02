#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include "aliascheck.h"

typedef void (*ptr_fun)();            // a function pointer typedef
typedef void* (*ptr_foo)(void*);            // a function pointer typedef

int Global;

void gplus(){
  Global++;
}

void *foo2(void *x) {
  printf("\t running foo2\n");
  Global ++;
  INTERLEV_ACCESS(2,"cs1.foo1,cs2.foo2","2,1,0");
  INTERLEV_ACCESS(3,"cs1.foo2","0,3");
  gplus();
  return x;
}

void *foo1(void *x) {
  printf("\t running foo1\n");
  pthread_t t2;
  Global ++;
  INTERLEV_ACCESS(1,"cs1.foo1","1,0");
cs2: pthread_create(&t2, NULL, foo2, NULL);
  Global ++;
  INTERLEV_ACCESS(1,"cs1.foo1","1,0,2");
  pthread_join(t2, NULL);
  Global ++;
  INTERLEV_ACCESS(1,"cs1.foo1","1,0");
  return x;
}

void dummy_function()
{
  printf("Running dummy function 1 \n");
  Global++;
}

void dummy_function2()
{
  printf("Running dummy function 2 \n");
  Global++;
}

int main(int argc, const char *argv[])
{
  pthread_t t1;
  int op = 0;
  ptr_fun ptr_dummy;
  ptr_foo ptr;

  printf("Enter dummy function to be executed (1 or 2)\n");
  char sel;
  sel = getchar();
  op = atoi(&sel);

  switch(op)
  {
    case 1: ptr_dummy = &dummy_function;
            ptr = &foo1;
            break;
    case 2: ptr_dummy = &dummy_function2;
            ptr = &foo2;
            break;
    default:
            return 0;
  }

  (*ptr_dummy)();                      //indirect call through function pointer
  Global++;
  INTERLEV_ACCESS(0,"","0");  
cs1: pthread_create(&t1, NULL, (*ptr), NULL);
  Global++;
  INTERLEV_ACCESS(0,"","0,1,2,3");  
  pthread_join(t1,NULL);

  Global++;
  INTERLEV_ACCESS(0,"","0");  

  CXT_THREAD(1,"cs1.foo1");
  CXT_THREAD(2,"cs1.foo1,cs2.foo2");
  CXT_THREAD(3,"cs1.foo2");
  TCT_ACCESS(0,"1,3");
  TCT_ACCESS(1,"2");

  return 0;
}
//todo: indirect call is like a branch? If I'm alive, you must be dead.
