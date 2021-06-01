/*
 * Simple alias check
 * Author: pengd 
 * Date: 07/07/2015
 */
#include "pthread.h"
#include "aliascheck.h"

pthread_t t1;
int Global;

void aa(){
  Global++;
   //If candidate function set is {main, foo2}
  INTERLEV_ACCESS(0,"cs2.gplus","0");  
  INTERLEV_ACCESS(0,"cs3.gplus","0,1");  
  INTERLEV_ACCESS(0,"cs4.gplus","0");  
  INTERLEV_ACCESS(1,"cs1.foo2,cs5.aa","0,1");  
  INTERLEV_ACCESS(1,"cs1.foo2,cs6.gplus","0,1");  

  INTERLEV_ACCESS(0,"cs10.bb","0");  
  INTERLEV_ACCESS(1,"cs1.foo2,cs9.bb","0,1");  

/*
   If candidate function set is {main, foo2, gplus, aa}

  INTERLEV_ACCESS(0,"cs2.gplus,cs7.aa","0");  
  INTERLEV_ACCESS(0,"cs3.gplus,cs7.aa","0,1");  
  INTERLEV_ACCESS(0,"cs4.gplus,cs7.aa","0");  
  INTERLEV_ACCESS(1,"cs1.foo2,cs5.aa","0,1");  
  INTERLEV_ACCESS(1,"cs1.foo2,cs6.gplus,cs7.aa","0,1");  

  INTERLEV_ACCESS(0,"cs10.bb,cs11.aa","0");  
  INTERLEV_ACCESS(1,"cs1.foo2,cs9.bb,cs11.aa","0,1");  


  INTERLEV_ACCESS(0,"cs2.gplus,cs8.bb,cs11.aa","0");  
  INTERLEV_ACCESS(0,"cs3.gplus,cs8.bb,cs11.aa","0,1");  
  INTERLEV_ACCESS(0,"cs4.gplus,cs8.bb,cs11..aa","0");  
  INTERLEV_ACCESS(1,"cs1.foo2,cs6.gplus,cs8.bb,cs11.aa","0,1");  

  */

}

void bb(){
cs11:  aa();
}

void gplus(){
  Global++;
  INTERLEV_ACCESS(0,"cs2.gplus","0");  
  INTERLEV_ACCESS(0,"cs3.gplus","0,1");  
  INTERLEV_ACCESS(0,"cs4.gplus","0");  
  INTERLEV_ACCESS(1,"cs1.foo2,cs6.gplus","0,1");  
cs7:  aa();
cs8:  bb();
}

void *foo2(void *x) {
  Global = 42;
cs5:  aa();
cs9:  bb();
cs6:  gplus();
  return x;
}

int main() {
  pthread_t t2;
 
cs10:  bb();
cs2:  gplus();
cs1:  pthread_create(&t2, NULL, foo2, NULL);
cs3:  gplus();
  pthread_join(t2, NULL);
cs4:  gplus();

  CXT_THREAD(1,"cs1.foo2");
  TCT_ACCESS(0,"1");
  
  return Global;
}
// In this case, different candidate function set make different check result
