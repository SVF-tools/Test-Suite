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
  INTERLEV_ACCESS(1,"cs1.Call,cs2.foo","0,1");  
  return x;
}

void Call(){
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0");  
  if (Global){
    Global ++;
    INTERLEV_ACCESS(0,"cs1.Call","0");  
cs2: pthread_create(&t1, NULL, foo, NULL);
     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,1");  
  }
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0,1");  
  if (Global){
    Global ++;
    INTERLEV_ACCESS(0,"cs1.Call","0,1");  
    pthread_join(t1, NULL);
    Global ++;
    INTERLEV_ACCESS(0,"cs1.Call","0");  
  }
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0,1");  
}

int main(){
  Global ++;
  INTERLEV_ACCESS(0,"","0");  
cs1: Call();
     Global ++;
     INTERLEV_ACCESS(0,"","0,1");  

     CXT_THREAD(1,"cs1.Call,cs2.foo");
     TCT_ACCESS(0,"1");
     return 1;
}
// CHECK: WARNING: ThreadSanitizer: data race
