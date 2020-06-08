/*
 * Simple program to test flow-sensitive analysis.
 * Author: Sen Ye
 * Date: 08/11/2013
 */

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
