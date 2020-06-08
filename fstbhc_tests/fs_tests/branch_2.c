/*
 * Branches for testing flow-sensitive analysis.
 * Author: Sen Ye
 * Date: 08/11/2013
 */

#include "tbhc_aliascheck.h"

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
