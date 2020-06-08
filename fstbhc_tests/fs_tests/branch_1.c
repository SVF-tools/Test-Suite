/*
 * Branches for testing flow-sensitive analysis.
 * Author: Sen Ye
 * Date: 08/11/2013
 */

#include "tbhc_aliascheck.h"

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
