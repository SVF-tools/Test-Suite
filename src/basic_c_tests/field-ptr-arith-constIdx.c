/*
 * Pointer arithmetic
 * Author: Sen Ye
 * Date: 06/09/2013
 */
#include "aliascheck.h"

struct s {
	int* f1;
	int* f2;
};

int main()
{
	int **q, **p;
	int a,b;
	struct s s1;
	s1.f1 = &a;
	s1.f2 = &b;
	q = &(s1.f1);
	p = q+1;
	MAYALIAS(*p,&b);
	return 0;
}
