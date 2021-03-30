/* Copied from fs_tests/ and modified to use TBHC macros. */
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
	TBHC_MUSTALIAS(*pp, *qq);
	return 0;
}
