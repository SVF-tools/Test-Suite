#include "aliascheck.h"
int **p,*x, y, z;

void f() {
  p = &x;
  if (1) {
    *p = &y;
	MUSTALIAS(x,&y);
    f();
    *p = &z;
	/// p doesn't point to x at the above line: although p's
	/// value changed by stmt "p=&x", the value flow can not
	/// reach "*p=&z" since it will flow into f() before
	/// "*p=&z" and connected with the entry of f(). So the
	/// store "*p=&z" can not be completed as p's pts is empty.
	NOALIAS(x,&z);
	NOALIAS(x,&y);
    f();
  }
}


int main()
{
    f();
    return 0;
}
