#include "aliascheck.h"

int main(){

  int **a, *b, *x ,c;
  c = 10;
  a = &b;
  b = &c;
  x = *a;
  int y = *x;
  MUSTALIAS(x,&c);
  MUSTALIAS(x,b);
  return 0;
}
