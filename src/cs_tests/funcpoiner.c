#include "aliascheck.h"
void f(int** a, int *b)
{
 *a = b; 
}

typedef void (*fp)(int**,int*);

void main()
{
        int **x,*y,*z;
        int *m,*n,m1,n1;
        m = &m1;
        n = &n1;
	fp p = &f;
	x = &y;
	(*p)(x,m);       /* these are equivalent */
        MUSTALIAS(y,m);
        NOALIAS(y,n);
	x = &z;
	p(x,n);
        MUSTALIAS(z,n);
        NOALIAS(z,m);
}

