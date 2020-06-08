/*
 * Simple program to test flow-sensitive analysis.
 * Author: Sen Ye
 * Date: 08/11/2013
 */

#include "tbhc_aliascheck.h"

int main() {
	int **p, **q;
	int *x, *y;
	int x0, y0;
	p = &x;
	q = &y;
	*p = &x0;
	*q = &y0;
	TBHC_NOALIAS(*p, *q);
	*p = *q;
	TBHC_MUSTALIAS(*p, *q);
	return 0;
}
