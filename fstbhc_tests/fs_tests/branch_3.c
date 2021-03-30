/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"

int main() {
	int **p, **q;
	int *x, *y;
	int x0, y0;
	if (x0) {
		p = &x;
		q = &y;
		TBHC_NOALIAS(p, q);
	}
	else {
		p = &y;
		q = &x;
		TBHC_NOALIAS(p, q);
	}
	TBHC_MAYALIAS(p, q);
	return 0;
}
