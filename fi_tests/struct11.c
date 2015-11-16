/*
 * Return a struct instance from function.
 * Author: Sen Ye
 * Date: 07/05/2014
 */
#include "aliascheck.h"

struct MyStruct {
	int* f1;
	char f2;
};

int x, y;

struct MyStruct foo() {
	struct MyStruct m;
	m.f1 = &x;
	return m;
}

int main() {
	struct MyStruct m;
	m = foo();
	EXPECTEDFAIL_MAYALIAS(m.f1, &x); /// This alias holds because m points to black hole object.
	NOALIAS(m.f1, &y);
	return 0;
}
