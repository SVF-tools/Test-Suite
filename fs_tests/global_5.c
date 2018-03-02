/*
 * Global pointer in flow-sensitive analysis.
 * Author: Sen Ye
 * Date: 08/11/2013
 */

#include "aliascheck.h"

int **pp, **qq;
int *p, *q;
int x;

void foo() {
	pp = &p;
	p = &x;
}

void bar() {
	qq = &q;
	q = &x;
}

int main() {
	foo();
	bar();
	MUSTALIAS(*pp, *qq);
	return 0;
}
