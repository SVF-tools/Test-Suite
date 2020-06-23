/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "tbhc_aliascheck.h"

int main() {
	int *p, *q;
	int x, y;
	p = &x;
	q = &y;
	TBHC_NOALIAS(p, q);
	p = q;
	TBHC_MUSTALIAS(p, q);
	return 0;
}
