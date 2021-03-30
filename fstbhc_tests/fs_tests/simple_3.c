/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"

int main() {
	int **p, **q;
	int *x, *y;
	int x0, y0;
	p = &x;
	q = &y;
	*p = &x0;
	*q = &y0;
	TBHC_NOALIAS(*p, *q);
	*p = *q;
	TBHC_MUSTALIAS(*p, *q);
	return 0;
}
