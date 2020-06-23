/*
 * Simple program to test flow-sensitive analysis.
 * Author: Sen Ye
 * Date: 08/11/2013
 */

#include "aliascheck.h"

int main() {
	int *p, *q, *r;
	int x, y, z;
	p = &x;
	q = &y;
	r = &z;
	NOALIAS(p, q);
	p = q;
	MUSTALIAS(p, q);
	p = r;
	NOALIAS(p, q);
	return 0;
}
