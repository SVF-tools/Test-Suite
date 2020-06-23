/*
 * Branches for testing flow-sensitive analysis.
 * Author: Sen Ye
 * Date: 08/11/2013
 */

#include "aliascheck.h"

int main() {
	int **p, **q;
	int *x, *y;
	int x0, y0;
	if (x0) {
		p = &x;
		q = &y;
		NOALIAS(p, q);
	}
	else {
		p = &y;
		q = &x;
		NOALIAS(p, q);
	}
	MAYALIAS(p, q);
	return 0;
}
