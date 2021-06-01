/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "aliascheck.h"
#include "pthread.h"


pthread_t t[5], t2;
int Global;

void *foo2(void *x) {
     Global ++;
     INTERLEV_ACCESS(2,"cs0.Call,cs1.foo1,cs2.foo2","0,1,2");  
     return x;
}
void *foo1(void *x) {
  Global ++;
  INTERLEV_ACCESS(1,"cs0.Call,cs1.foo1","0,1,2");  

cs2: pthread_create(&t2, NULL, foo2, NULL);

     Global ++;
     INTERLEV_ACCESS(1,"cs0.Call,cs1.foo1","0,1,2");  

     pthread_join(t2, NULL);

     Global ++;
     INTERLEV_ACCESS(1,"cs0.Call,cs1.foo1","0,1,2");  
     return x;
}

void Call(){
  Global ++;
  INTERLEV_ACCESS(0,"cs0.Call","0");  

  for (int i = 0; i<5;i++){
    cs1: pthread_create(&t[i], NULL, foo1, NULL);
  }
  Global ++;
  INTERLEV_ACCESS(0,"cs0.Call","0,1,2");  

  for (int i = 0; i<5;i++){
    if (i==2)
      continue;
    pthread_join(t[i], NULL);
  }
  Global ++;
  INTERLEV_ACCESS(0,"cs0.Call","0,1,2");  
}

int main(){

  Global ++;
  INTERLEV_ACCESS(0,"","0");  

cs0: Call();

     Global ++;
     INTERLEV_ACCESS(0,"","0,1,2");  

     CXT_THREAD(1,"cs0.Call,cs1.foo1");
     CXT_THREAD(2,"cs0.Call,cs1.foo1,cs2.foo2");
     TCT_ACCESS(0,"1");
     TCT_ACCESS(1,"2");
     return 1;
}
// todo
