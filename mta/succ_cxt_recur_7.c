/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "aliascheck.h"
#include "pthread.h"


pthread_t t1,t2;
pthread_t t[5];
int Global;
int tid;
void Call(int);

void *foo2(void *x) {
  Global = 0;
  INTERLEV_ACCESS(2,"cs1.Call,cs2.Create,cs4.foo1,cs5.foo2","0,1,2");  
  return x;
}

void *foo1(void *x) {
  Global ++;
  INTERLEV_ACCESS(1,"cs1.Call,cs2.Create,cs4.foo1","0,1,2");  

cs5: pthread_create(&t2, NULL, foo2, NULL);

     Global ++;
     INTERLEV_ACCESS(1,"cs1.Call,cs2.Create,cs4.foo1","0,1,2");  

     pthread_join(t2, NULL);

     Global ++;
     INTERLEV_ACCESS(1,"cs1.Call,cs2.Create,cs4.foo1","0,1,2");  
     return x;
}

void Create(int i){
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call,cs2.Create","0,1,2");  
cs4: pthread_create(&t[i], NULL, foo1, NULL);
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call,cs2.Create","0,1,2");  
}
/*
void Join(int i){
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call,cs3.Join","0,1,2");  
  pthread_join(t[i], NULL);
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call,cs3.Join","0,1,2");  
}
*/
void Call2(int tid){
  Call(tid);
}

void Call(int tid){
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0,1,2");  

  if (tid<5){
cs2: Create(tid);

     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,1,2");  

     Call2(tid+1);
     
     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,1,2");  
    
//cs3: Join(tid);
    
     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,1,2");  

  }
     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,1,2");  
}

int main(){

  Global=0;
  INTERLEV_ACCESS(0,"","0");  

cs1: Call(1);

     Global ++;
     INTERLEV_ACCESS(0,"","0,1,2");  

     CXT_THREAD(1,"cs1.Call,cs2.Create,cs4.foo1");
     CXT_THREAD(2,"cs1.Call,cs2.Create,cs4.foo1,cs5.foo2");
     TCT_ACCESS(0,"1");
     TCT_ACCESS(1,"2");
     return 1;
}
