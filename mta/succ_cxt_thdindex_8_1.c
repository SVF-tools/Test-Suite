/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "aliascheck.h"
#include "pthread.h"


pthread_t t[5];
int Global;

void *foo2(void *x) {
  printf("Call thread id %u \n", (unsigned int)pthread_self());
     
  PAUSE("foo2");
  Global ++;
  INTERLEV_ACCESS(2,"cs1.foo1,cs3.foo2","0,1,2,3,4");  
  INTERLEV_ACCESS(4,"cs2.foo1,cs3.foo2","0,3,4,1,2");  
  return x;
}

void *foo1(void *x) {

  pthread_t t;
  printf("Call thread id %u \n", (unsigned int)pthread_self());
  Global ++;
  INTERLEV_ACCESS(1,"cs1.foo1","0,1,3,4");  
  INTERLEV_ACCESS(3,"cs2.foo1","0,3,1,2");  
     
  PAUSE("foo1.before cs3");

cs3: pthread_create(&t, NULL, foo2, NULL);

     PAUSE("foo1 after cs3");

     Global ++;
     INTERLEV_ACCESS(1,"cs1.foo1","0,1,2,3,4");  
     INTERLEV_ACCESS(3,"cs2.foo1","0,3,4,1,2");  

     pthread_join(t, NULL);

     PAUSE("foo1 after join 3");

     Global ++;
     INTERLEV_ACCESS(1,"cs1.foo1","0,1,3,4");  
     INTERLEV_ACCESS(3,"cs2.foo1","0,3,1,2");  
     return x;
}

int main(){
  printf("Call thread id %u \n", (unsigned int)pthread_self());
  Global ++;
  INTERLEV_ACCESS(0,"","0");  

     PAUSE("main before cs1");
cs1: pthread_create(&t[0], NULL, foo1, NULL);

     PAUSE("main after cs1");

     Global ++;
     INTERLEV_ACCESS(0,"","0,1,2");  

cs2: pthread_create(&t[1], NULL, foo1, NULL);

     PAUSE("main after cs2");

     Global ++;
     INTERLEV_ACCESS(0,"","0,1,2,3,4");  

     pthread_join(t[4], NULL);
     
     PAUSE("main after join 1");
     
     Global ++;
     INTERLEV_ACCESS(0,"","0,1,2,3,4");  

     pthread_join(t[4], NULL);

     PAUSE("main after join 2");
     Global ++;
     INTERLEV_ACCESS(0,"","0,1,2,3,4");  

     CXT_THREAD(1,"cs1.foo1");
     CXT_THREAD(2,"cs1.foo1,cs3.foo2");
     CXT_THREAD(3,"cs2.foo1");
     CXT_THREAD(4,"cs2.foo1,cs3.foo2");
     TCT_ACCESS(0,"1,3");
     TCT_ACCESS(1,"2");
     TCT_ACCESS(3,"4");
     return 1;
}
