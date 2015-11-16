/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "aliascheck.h"
#include "pthread.h"

pthread_t t1,t2,t3,t4,t5,t6;
int Global;

void *foo(void *x) {
  Global ++;

  INTERLEV_ACCESS(3,"cs1.Call,cs2.foo1,cs4.ffoo1,cs8.foo","0,1,2,3");  
  INTERLEV_ACCESS(6,"cs1.Call,cs6.foo2,cs5.ffoo2,cs9.foo","0,4,5,6");  
  return x;
}

void *ffoo1(void *x) {

  Global ++;

  INTERLEV_ACCESS(2,"cs1.Call,cs2.foo1,cs4.ffoo1","0,1,2");  

cs8: pthread_create(&t3, NULL, foo, NULL);

     Global ++;
     INTERLEV_ACCESS(2,"cs1.Call,cs2.foo1,cs4.ffoo1","0,1,2,3");  

     pthread_join(t3, NULL);

     Global ++;
     INTERLEV_ACCESS(2,"cs1.Call,cs2.foo1,cs4.ffoo1","0,1,2");  
     return x;
}

void *ffoo2(void *x) {

  Global ++;
  INTERLEV_ACCESS(5,"cs1.Call,cs6.foo2,cs5.ffoo2","0,4,5");  

cs9: pthread_create(&t6, NULL, foo, NULL);

     Global ++;
     INTERLEV_ACCESS(5,"cs1.Call,cs6.foo2,cs5.ffoo2","0,4,5,6");  

     pthread_join(t6, NULL);

     Global ++;
     INTERLEV_ACCESS(5,"cs1.Call,cs6.foo2,cs5.ffoo2","0,4,5");  
     return x;
}

void *foo1(void *x) {

  Global ++;

  INTERLEV_ACCESS(1,"cs1.Call,cs2.foo1","0,1");  

cs4: pthread_create(&t2, NULL, ffoo1, NULL);

     Global ++;
     INTERLEV_ACCESS(1,"cs1.Call,cs2.foo1","0,1,2,3");  

     pthread_join(t2, NULL);

     Global ++;
     INTERLEV_ACCESS(1,"cs1.Call,cs2.foo1","0,1");  
     return x;
}

void *foo2(void *x) {

  Global ++;
  INTERLEV_ACCESS(4,"cs1.Call,cs6.foo2","0,4");  

cs5: pthread_create(&t5, NULL, ffoo2, NULL);

     Global ++;
     INTERLEV_ACCESS(4,"cs1.Call,cs6.foo2","0,4,5,6");  

//     pthread_join(t5, NULL);

     Global ++;
     INTERLEV_ACCESS(4,"cs1.Call,cs6.foo2","0,4,5,6");  
     return x;
}

void Call(){
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0");  

cs2: pthread_create(&t1, NULL, foo1, NULL);

     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,1,2,3");  

cs3: pthread_join(t1, NULL);

     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0");  

cs6: pthread_create(&t4, NULL, foo2, NULL);

     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,4,5,6");  

cs7: pthread_join(t4, NULL);

     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,5,6");  
}

int main(){

  Global ++;
  INTERLEV_ACCESS(0,"","0");  

cs1: Call();

     Global ++;
     INTERLEV_ACCESS(0,"","0,5,6");  

     CXT_THREAD(1,"cs1.Call,cs2.foo1");
     CXT_THREAD(2,"cs1.Call,cs2.foo1,cs4.ffoo1");
     CXT_THREAD(3,"cs1.Call,cs2.foo1,cs4.ffoo1,cs8.foo");
     CXT_THREAD(4,"cs1.Call,cs6.foo2");
     CXT_THREAD(5,"cs1.Call,cs6.foo2,cs5.ffoo2");  
     CXT_THREAD(6,"cs1.Call,cs6.foo2,cs5.ffoo2,cs9.foo");  
     TCT_ACCESS(0,"1,4");
     TCT_ACCESS(1,"2");
     TCT_ACCESS(2,"3");
     TCT_ACCESS(4,"5");
     TCT_ACCESS(5,"6");
     return 1;
}
// todo: handle executing sequential of partial join
