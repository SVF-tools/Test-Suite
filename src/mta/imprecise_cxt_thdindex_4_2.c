/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "aliascheck.h"
#include "pthread.h"


pthread_t tt[2];
pthread_t ttt[2];
pthread_t t;
int Global;

void *foo2(void *x) {
  printf("foo2 thread id %u \n", (unsigned int)pthread_self());
  Global = 42;
  INTERLEV_ACCESS(2,"cs1.Call,cs2.Create,cs4.foo1,cs5.foo2","0,1,2,3,4");  
  INTERLEV_ACCESS(4,"cs1.Call,cs6.Create,cs4.foo1,cs5.foo2","0,3,4,1,2");  
  return x;
}

void *foo1(void *x) {

  int* tid = x;
  
  printf("foo1 thread id %u \n", (unsigned int)pthread_self());
  Global ++;
  INTERLEV_ACCESS(1,"cs1.Call,cs2.Create,cs4.foo1","0,1,3,4");  
  INTERLEV_ACCESS(3,"cs1.Call,cs6.Create,cs4.foo1","0,3,1,2");  

cs5: pthread_create(&ttt[*tid], NULL, foo2, NULL);

     Global ++;
     INTERLEV_ACCESS(1,"cs1.Call,cs2.Create,cs4.foo1","0,1,2,3,4");  
     INTERLEV_ACCESS(3,"cs1.Call,cs6.Create,cs4.foo1","0,3,4,1,2");  

     pthread_join(ttt[*tid], NULL);

     Global ++;
     INTERLEV_ACCESS(1,"cs1.Call,cs2.Create,cs4.foo1","0,1,3,4");  
     INTERLEV_ACCESS(3,"cs1.Call,cs6.Create,cs4.foo1","0,3,1,2");  
     return x;
}

void Create(int i){
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call,cs2.Create","0");  
  INTERLEV_ACCESS(0,"cs1.Call,cs6.Create","0,1,2");  
  void * ptr =  &i;
  
cs4: pthread_create(&tt[i], NULL, foo1, ptr);
     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call,cs2.Create","0,1,2");  
     INTERLEV_ACCESS(0,"cs1.Call,cs6.Create","0,3,4,1,2");  
}

void Join(int i){
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call,cs3.Join","0,1,2,3,4");  
  INTERLEV_ACCESS(0,"cs1.Call,cs7.Join","0,3,4");  
  pthread_join(tt[i], NULL);
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call,cs3.Join","0,3,4");  
  INTERLEV_ACCESS(0,"cs1.Call,cs7.Join","0");  
}

void Call(){
  printf("Call thread id %u \n", (unsigned int)pthread_self());
  Global ++;
  INTERLEV_ACCESS(0,"cs1.Call","0");  

cs2: Create(0);

     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,1,2");  

cs6: Create(1);

     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,1,2,3,4");  

cs3: Join(0);

     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0,3,4");  

cs7: Join(1);

     Global ++;
     INTERLEV_ACCESS(0,"cs1.Call","0");  
}

int main(){

  Global ++;
  INTERLEV_ACCESS(0,"","0");  

cs1: Call();

     Global ++;
     INTERLEV_ACCESS(0,"","0");  

     CXT_THREAD(1,"cs1.Call,cs2.Create,cs4.foo1");
     CXT_THREAD(2,"cs1.Call,cs2.Create,cs4.foo1,cs5.foo2");
     CXT_THREAD(3,"cs1.Call,cs6.Create,cs4.foo1");
     CXT_THREAD(4,"cs1.Call,cs6.Create,cs4.foo1,cs5.foo2");
     TCT_ACCESS(0,"1,3");
     TCT_ACCESS(1,"2");
     TCT_ACCESS(3,"4");
     return 1;
}
