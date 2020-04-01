/*
 * Function pointer.
 * Author: Sen Ye
 * Date: 10/10/2013
 */
#include "aliascheck.h"


void func1(int **p, int **q) {
	*p = *q;
	MUSTALIAS(p, q);
}

void (*fp)(int**,int**);

int main() {
	int o1, o2;
	int *x, *y;
	int **m, **n;
	x = &o1;
	y = &o2;
	m = &x;
	n = &x;
	fp = func1;
	fp(m,n);
	NOALIAS(x, y);
	return 0;
}
