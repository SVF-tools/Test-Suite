/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "aliascheck.h"
#include "pthread.h"


pthread_t t1;
int Global;
int g1, g2;

int *p2;
int **p4;
int **p5;

void *foo(void *x) {

  int *p3;
  p2=&Global;
  p3=p2;
  p3=*p4;
  Global = 42;
  INTERLEV_ACCESS(1,"cs1.Call,cs2.foo","0,1");  
  return x;
}

void Call(){
  **p4=Global;
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0");  
cs2: pthread_create(&t1, NULL, foo, NULL);
  Global ++;
  p2=*p5;
  INTERLEV_ACCESS(0,"cs1.Call","0,1");  
  pthread_join(t1, NULL);
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0");  
}

int main(){
 
  int l1,l2;
  int* p1;
  Global ++;
  p1=&l1;
  (*p1)++;
  p2=p1;
  INTERLEV_ACCESS(0,"","0");  
cs1: Call();
  Global ++;
  INTERLEV_ACCESS(0,"","0");  

  CXT_THREAD(1,"cs1.Call,cs2.foo");
  TCT_ACCESS(0,"1");
  return 1;
}
// CHECK: WARNING: ThreadSanitizer: data race
