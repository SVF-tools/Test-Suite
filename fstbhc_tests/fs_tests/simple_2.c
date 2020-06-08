/*
 * Simple program to test flow-sensitive analysis.
 * Author: Sen Ye
 * Date: 08/11/2013
 */

#include "tbhc_aliascheck.h"

int main() {
	int *p, *q, *r;
	int x, y, z;
	p = &x;
	q = &y;
	r = &z;
	TBHC_NOALIAS(p, q);
	p = q;
	TBHC_MUSTALIAS(p, q);
	p = r;
	TBHC_NOALIAS(p, q);
	return 0;
}
