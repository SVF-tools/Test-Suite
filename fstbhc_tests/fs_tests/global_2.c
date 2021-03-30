/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"

int **pp, **qq;
int *p, *q;
int x, y;

void foo() {
	pp = &p;
	p = &x;
	qq = &q;
	q = &y;
	TBHC_NOALIAS(*pp, *qq);
}

void bar() {
	qq = &q;
	q = &x;
}

int main() {
	foo();
	bar();
	TBHC_MUSTALIAS(*pp, *qq);
	return 0;
}
