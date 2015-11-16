/*
 * Alias due to lack of path-sensitivity.
 * Author: Sen Ye
 * Date: 06/09/2013
 */
#include "aliascheck.h"

int main()
{
	int *p, *q;
	int a, b, c;
	if (c) {
		p = &a;
		q = &b;
	}
	else {
		p = &b;
		q = &c;
	}
	MAYALIAS(p,q);
	return 0;
}
