/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "aliascheck.h"
#include "pthread.h"


pthread_t t1;
int Global;

void gplus(){
  Global++;
  INTERLEV_ACCESS(0,"cs2.gplus","0");  
  INTERLEV_ACCESS(0,"cs4.gplus","0,1,2");  
  INTERLEV_ACCESS(0,"cs5.gplus","0");  
  INTERLEV_ACCESS(1,"cs3.foo1,cs1.gplus","0,1,2");  
  INTERLEV_ACCESS(2,"cs3.foo1,cs0.foo2,cs6.gplus","0,1,2");  
}

void *foo2(void *x) {
  Global = 42;
  INTERLEV_ACCESS(2,"cs3.foo1,cs0.foo2","0,1,2");  
cs6: gplus();
  return x;
}

void *foo1(void *x) {
  Global = 42;
  INTERLEV_ACCESS(1,"cs3.foo1","0,1");  

  pthread_t t2;
  if(Global){
  
    Global = 42;
    INTERLEV_ACCESS(1,"cs3.foo1","0,1");  

cs0: pthread_create(&t2, NULL, foo2, NULL);
     
cs1: gplus();

    Global ++;
    INTERLEV_ACCESS(1,"cs3.foo1","0,1,2");  

    pthread_join(t2, NULL);

    Global ++;
    INTERLEV_ACCESS(1,"cs3.foo1","0,1");  
  }
  else{
    Global ++;
    INTERLEV_ACCESS(1,"cs3.foo1","0,1");  
  }
    
  Global ++;
  INTERLEV_ACCESS(1,"cs3.foo1","0,1");  

  return x;
}

int main() {
  pthread_t t1;
  
  Global =399;
  INTERLEV_ACCESS(0,"","0");  

cs2: gplus();
cs3: pthread_create(&t1, NULL, foo1, NULL);

  Global --;
  INTERLEV_ACCESS(0,"","0,1,2");  

cs4: gplus();
  pthread_join(t1, NULL);

  Global ++;
  INTERLEV_ACCESS(0,"","0");  

cs5: gplus();
  
  CXT_THREAD(1,"cs3.foo1");
  CXT_THREAD(2,"cs3.foo1,cs0.foo2");

  TCT_ACCESS(0,"1");
  TCT_ACCESS(1,"2");
  return Global;
}
