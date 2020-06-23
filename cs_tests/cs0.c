#include "aliascheck.h"
int* foo(int* x){
   return x;
}

int main(){

  int *x,*y,*p,*q,a,b;
  p = &a;
  q = &b;
  x = foo(p);
  y = foo(q);
  MUSTALIAS(x,p);
  MUSTALIAS(y,q);
  NOALIAS(x,q);
  NOALIAS(y,p);

}
