/*
 * Global variable
 * Author: Sen Ye
 * Date: 13/10/2013
 * Description: Initialise global variables in callee and check alias
 *		in caller.
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
	MAYALIAS(*pp, *qq);
	foo();
	bar();
	return 0;
}
