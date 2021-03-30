/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"

int main() {
	int *p, *q;
	int x, y;
	if (x)
		p = &x;
	else
		p = &y;
	q = &y;
	TBHC_MAYALIAS(p, q);
	return 0;
}
