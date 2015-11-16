/*
 * Branches for testing flow-sensitive analysis.
 * Author: Sen Ye
 * Date: 08/11/2013
 */

#include "aliascheck.h"

int main() {
	int *p, *q;
	int x, y;
	q = &y;
	if (x) {
		p = &x;
		NOALIAS(p, q);
	}
	else {
		p = &y;
		MUSTALIAS(p, q);
	}
	return 0;
}
