/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "aliascheck.h"
#include "pthread.h"


pthread_t t;
int Global;

void *foo(void *x) {
  Global = 42;
  INTERLEV_ACCESS(1,"cs0.Call,cs1.foo","0,1");  
  return x;
}

void Call() {
  Global = 42;
  INTERLEV_ACCESS(0,"cs0.Call","0");  

  if(Global){
  
    Global = 42;
    INTERLEV_ACCESS(0,"cs0.Call","0");  

cs1: pthread_create(&t, NULL, foo, NULL);
     
    Global ++;
    INTERLEV_ACCESS(0,"cs0.Call","0,1");  

    pthread_join(t, NULL);

    Global ++;
    INTERLEV_ACCESS(0,"cs0.Call","0");  
  }
  else{
    Global ++;
    INTERLEV_ACCESS(0,"cs0.Call","0");  
  }
    
  Global ++;
  INTERLEV_ACCESS(0,"cs0.Call","0");  
}

int main() {
  
  Global =399;
  INTERLEV_ACCESS(0,"","0");  

cs0: Call();

  Global ++;
  INTERLEV_ACCESS(0,"","0");  
  
  CXT_THREAD(1,"cs0.Call,cs1.foo");

  TCT_ACCESS(0,"1");
  return Global;
}
