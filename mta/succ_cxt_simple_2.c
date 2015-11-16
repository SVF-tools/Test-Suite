/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "aliascheck.h"
#include "pthread.h"


pthread_t t1;
int Global;

void *foo(void *x) {
  Global = 42;
  INTERLEV_ACCESS(1,"cs1.Call,cs2.Create,cs4.foo","0,1");  
  return x;
}

void Create(){
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call,cs2.Create","0");  
cs4: pthread_create(&t1, NULL, foo, NULL);
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call,cs2.Create","0,1");  
}
void Join(){
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call,cs3.Join","0,1");  
  pthread_join(t1, NULL);
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call,cs3.Join","0");  
}

void Call(){
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0");  
cs2: Create();
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0,1");  
cs3: Join();
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0");  
}

int main(){
  Global ++;
  INTERLEV_ACCESS(0,"","0");  
cs1: Call();
  Global ++;
  INTERLEV_ACCESS(0,"","0");  

  CXT_THREAD(1,"cs1.Call,cs2.Create,cs4.foo");
  TCT_ACCESS(0,"1");
  return 1;
}
// CHECK: WARNING: ThreadSanitizer: data race
