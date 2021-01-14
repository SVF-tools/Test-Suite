#include "aliascheck.h"
int **p,*x, y, z;

void f() {
  p = &x;
  if (z) {
    *p = &y;
	MUSTALIAS(x,&y);
    f();
    *p = &z;
	MAYALIAS(x,&z);
	NOALIAS(x,&y);
    f();
  }
}


int main()
{
    f();
    return 0;
}
