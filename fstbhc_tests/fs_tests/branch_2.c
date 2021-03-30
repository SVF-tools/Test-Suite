/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"

int main() {
	int *p, *q;
	int x, y;
	q = &y;
	if (x) {
		p = &x;
		TBHC_NOALIAS(p, q);
	}
	else {
		p = &y;
		TBHC_MUSTALIAS(p, q);
	}
	return 0;
}
