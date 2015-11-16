/*
 * Function pointer.
 * Author: Sen Ye
 * Date: 10/10/2013
 */
#include "aliascheck.h"

void func1(int **p, int **q) {
	*p = *q;
}

void (*fp)(int**,int**);

int main() {
	int o1, o2;
	int *x, *y;
	int **m, **n;
	x = &o1;
	y = &o2;
	m = &x;
	n = &y;
	fp = func1;
	fp(m,n);
	MUSTALIAS(x, y);
	return 0;
}
