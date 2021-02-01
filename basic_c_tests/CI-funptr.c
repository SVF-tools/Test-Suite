/*
 * Alias due to function pointer resolution.
 * Author: Sen Ye
 * Date: 06/09/2013
 */
#include "aliascheck.h"

void f(int *m, int *n)
{
	MAYALIAS(m, n);
}

typedef void (*fp)(int*m, int*n);

int main()
{
	int a,b,c,d;
	int *pa, *pb;
    fp p;
	pa = &a, pb = &b;
	f(pa, pb);
    p = f;
	pb = &a;
    (*p)(pa, pb); 
	return 0;
}

