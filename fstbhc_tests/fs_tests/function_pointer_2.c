/* Copied from fs_tests/ and modified to use TBHC macros. */
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
	TBHC_MUSTALIAS(x, y);
	return 0;
}
