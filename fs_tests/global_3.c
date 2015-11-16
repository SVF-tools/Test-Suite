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
	*pp = &x;
}

void bar() {
	qq = &q;
	q = &x;
}

int main() {
	pp = &p;
	foo();
	bar();
	MUSTALIAS(*pp, *qq);
	return 0;
}
