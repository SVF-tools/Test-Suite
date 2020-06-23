/*
 * Simple program to test flow-sensitive analysis.
 * Author: Sen Ye
 * Date: 08/11/2013
 */

#include "aliascheck.h"

int main() {
	int *p, *q;
	int x, y;
	p = &x;
	q = &y;
	NOALIAS(p, q);
	p = q;
	MUSTALIAS(p, q);
	return 0;
}
