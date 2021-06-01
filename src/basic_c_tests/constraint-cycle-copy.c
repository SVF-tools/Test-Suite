/*
 * Cycle
 * Author: Sen Ye
 * Date: 11/10/2013
 */
#include "aliascheck.h"

int main() {
	int **x1, **y1, **z1;
	int *x2, *y2, *z2, *y2_;
	int x3, y3, z3, y3_;
	x2 = &x3, y2 = &y3, z2 = &z3;
	x1 = &x2, y1 = &y2, z1 = &z2;
	// if the following branch is commented out,
	// the first alias check will fail while
	// the second one is OK.
	if (y3_) {
		y1 = &y2_;
		y2_ = &y3_;
	}
	*x1 = *y1;
	*y1 = *z1;
	*z1 = *x1;
	// there should be a cycle from
	// y2 -> x2 -> z2 -> y2
	MAYALIAS(x2, y2);
	MAYALIAS(z2, x2);
	return 0;
}
