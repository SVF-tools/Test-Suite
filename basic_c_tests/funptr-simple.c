/*
 * Function pointer.
 * Author: Sen Ye
 * Date: 10/10/2013
 */
#include "aliascheck.h"

void f(int *p, int *q) {
	// if function pointer solved correctly,
	// p and q will alias due to CS1
	MAYALIAS(p,q);
}

void (*fptr)(int*,int*);

int main() {
	int x, y;
	int *m, *n;
	if (x) {
		m = &x, n = &x;
		fptr = f;
		fptr(m,n); // CS1
	}
	else {
		m = &x; n = &y;
		f(m,n); // CS2
	}
	return 0;
}
