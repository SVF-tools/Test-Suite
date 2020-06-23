/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "aliascheck.h"
#include "pthread.h"


pthread_t t1,t2;
int Global;

void *foo2(void *x) {
  Global = 42;
  INTERLEV_ACCESS(2,"cs1.Call,cs2.foo1,cs3.foo2","0,1,2");  
  return x;
}

void *foo1(void *x) {
  Global ++;
  INTERLEV_ACCESS(1,"cs1.Call,cs2.foo1","0,1");  

cs3: pthread_create(&t2, NULL, foo2, NULL);

     Global ++;
     INTERLEV_ACCESS(1,"cs1.Call,cs2.foo1","0,1,2");  

     pthread_join(t2, NULL);

     Global ++;
     INTERLEV_ACCESS(1,"cs1.Call,cs2.foo1","0,1");  
     return x;
}

void Call(){
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0");  

cs2: pthread_create(&t1, NULL, foo1, NULL);

     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,1,2");  

//     pthread_join(t1, NULL);

     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,1,2");  
}

int main(){

  Global ++;
  INTERLEV_ACCESS(0,"","0");  

cs1: Call();

     Global ++;
     INTERLEV_ACCESS(0,"","0,1,2");  

     CXT_THREAD(1,"cs1.Call,cs2.foo1");
     CXT_THREAD(2,"cs1.Call,cs2.foo1,cs3.foo2");
     TCT_ACCESS(0,"1");
     TCT_ACCESS(1,"2");
     return 1;
}
// CHECK: WARNING: ThreadSanitizer: data race
