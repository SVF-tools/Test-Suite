/*
 * Global variables test.
 * Author: Sen Ye
 * Date: 03/05/2014
 */
#include "aliascheck.h"

int *p = NULL;
int *q = NULL;
int c;

void foo() {
	MAYALIAS(p, q);
}

void bar() {
	q = &c;
}

int main() {
	int a, b;
	p = &a;
	q = p;
	p = &c;
}
