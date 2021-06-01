/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "aliascheck.h"
#include "pthread.h"


pthread_t t1, t2[5], t3, t4;
int Global;

void *foo4(void *x) {
  Global ++;
  INTERLEV_ACCESS(4,"cs0.Call,cs1.foo1,cs2.foo2,cs3.foo3,cs4.foo4","0,1,2,3,4");  
  return x;
}

void *foo3(void *x) {
  Global ++;
  INTERLEV_ACCESS(3,"cs0.Call,cs1.foo1,cs2.foo2,cs3.foo3","0,1,2,3,4");  

cs4: pthread_create(&t4, NULL, foo4, NULL);

     Global ++;
     INTERLEV_ACCESS(3,"cs0.Call,cs1.foo1,cs2.foo2,cs3.foo3","0,1,2,3,4");  

     pthread_join(t4, NULL);

     Global ++;
     INTERLEV_ACCESS(3,"cs0.Call,cs1.foo1,cs2.foo2,cs3.foo3","0,1,2,3,4");  
     return x;
}

void *foo2(void *x) {
  Global ++;
  INTERLEV_ACCESS(2,"cs0.Call,cs1.foo1,cs2.foo2","0,1,2,3,4");  

cs3: pthread_create(&t3, NULL, foo3, NULL);

     Global ++;
     INTERLEV_ACCESS(2,"cs0.Call,cs1.foo1,cs2.foo2","0,1,2,3,4");  

     pthread_join(t3, NULL);

     Global ++;
     INTERLEV_ACCESS(2,"cs0.Call,cs1.foo1,cs2.foo2","0,1,2,3,4");  
     return x;
}

void *foo1(void *x) {
  Global ++;
  INTERLEV_ACCESS(1,"cs0.Call,cs1.foo1","0,1");  

  for (int i = 0; i<5;i++){
cs2: pthread_create(&t2[i], NULL, foo2, NULL);
  }
  Global ++;
  INTERLEV_ACCESS(1,"cs0.Call,cs1.foo1","0,1,2,3,4");  

  for (int i = 0; i<5;i++){
    pthread_join(t2[i], NULL);
  }
  Global ++;
  INTERLEV_ACCESS(1,"cs0.Call,cs1.foo1","0,1");  
  return x;
}

void Call(){
  Global ++;
  INTERLEV_ACCESS(0,"cs0.Call","0");  
cs1: pthread_create(&t1, NULL, foo1, NULL);
     Global ++;
     INTERLEV_ACCESS(0,"cs0.Call","0,1,2,3,4");  
     pthread_join(t1, NULL);
     Global ++;
     INTERLEV_ACCESS(0,"cs0.Call","0");  

}


int main(){

  Global ++;
  INTERLEV_ACCESS(0,"","0");  

cs0: Call();

     Global ++;
     INTERLEV_ACCESS(0,"","0");  

     CXT_THREAD(1,"cs0.Call,cs1.foo1");
     CXT_THREAD(2,"cs0.Call,cs1.foo1,cs2.foo2");
     CXT_THREAD(3,"cs0.Call,cs1.foo1,cs2.foo2,cs3.foo3");
     CXT_THREAD(4,"cs0.Call,cs1.foo1,cs2.foo2,cs3.foo3,cs4.foo4");
     TCT_ACCESS(0,"1");
     TCT_ACCESS(1,"2");
     TCT_ACCESS(2,"3");
     TCT_ACCESS(3,"4");
     return 1;
}
