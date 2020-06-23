#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include "aliascheck.h"

typedef int (*ptr_fun)();            // a function pointer typedef
typedef void* (*ptr_foo)(void*);            // a function pointer typedef

int Global;

void gplus(){
  Global++;
}

void *foo4(void *x) {
  Global ++;
  INTERLEV_ACCESS(5,"cs1.foo1,cs2.foo2,cs3.foo4","2,1,0,4");
  INTERLEV_ACCESS(7,"cs1.foo2,cs3.foo4","0,3,6");
  return x;
}
void *foo3(void *x) {
  Global ++;

  INTERLEV_ACCESS(4,"cs1.foo1,cs2.foo2,cs3.foo3","2,1,0,4");
  INTERLEV_ACCESS(6,"cs1.foo2,cs3.foo3","0,3,6");
  gplus();
  return x;
}
void *foo2(void *x) {
  printf("\t running foo2\n");
  Global ++;
  INTERLEV_ACCESS(2,"cs1.foo1,cs2.foo2","2,1,0");
  INTERLEV_ACCESS(3,"cs1.foo2","0,3");
  gplus();
  
  ptr_foo ptr;
  
  switch(Global%3)
  {
    case 1: ptr = &foo3;
            break;
    case 2: ptr = &foo4;
            break;
    default:
            return 0;
  }
  pthread_t t3;
cs3: pthread_create(&t3, NULL, (*ptr), NULL);
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
  INTERLEV_ACCESS(1,"cs1.foo1","1,0,4,5,6,7");
  return x;
}

int dummy_function()
{
  printf("Running dummy function 1 \n");
  Global++;
  return Global;
}

int dummy_function2()
{
  printf("Running dummy function 2 \n");
  Global++;

  return Global;
}

void call(int op){
  ptr_fun ptr_dummy;
  switch(op)
  {
    case 1: ptr_dummy = &dummy_function;
            break;
    case 2: ptr_dummy = &dummy_function2;
            break;
    case 3: ptr_dummy = &getchar;
            break;
    default:
            break;
  }
  (*ptr_dummy)();                      //indirect call through function pointer
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

  call(op);

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
  INTERLEV_ACCESS(0,"","0,1,2,3,4,5,6,7");  
  pthread_join(t1,NULL);

  Global++;
  INTERLEV_ACCESS(0,"","0,4,5,6,7");  

  CXT_THREAD(1,"cs1.foo1");
  CXT_THREAD(2,"cs1.foo1,cs2.foo2");
  CXT_THREAD(3,"cs1.foo2");
  CXT_THREAD(4,"cs1.foo1,cs2.foo2,cs3.foo3");
  CXT_THREAD(5,"cs1.foo1,cs2.foo2,cs3.foo4");
  CXT_THREAD(6,"cs1.foo2,cs3.foo3");
  CXT_THREAD(7,"cs1.foo2,cs3.foo4");

  TCT_ACCESS(0,"1,3");
  TCT_ACCESS(1,"2");
  TCT_ACCESS(2,"4,5");
  TCT_ACCESS(3,"6,7");

  return 0;
}
//todo: indirect call is like a branch? If I'm alive, you must be dead.
