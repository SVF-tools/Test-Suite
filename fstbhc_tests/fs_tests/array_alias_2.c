/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"

struct MyStruct {
	int * f1;
	int * f2;
	float * f3;
};

int main() {
	struct MyStruct s[3];
	int * p[2];
	int a,b,c,d;
	float x,y;
	s[0].f1 = &a, s[0].f2 = &c, s[0].f3 = &x;
	s[1].f1 = &b, s[1].f2 = &d, s[1].f3 = &y;
	p[0] = &c, p[1] = &d;

	// Same fields of different elements in a certain
	// array are treated as one object.
	TBHC_MAYALIAS(s[0].f1, s[1].f1);
	TBHC_MAYALIAS(p[0], s[1].f2);
	TBHC_MAYALIAS(s[0].f3, &y);

	// Different fields of different elements in a 
	// certain array are treated as different objects.
	TBHC_NOALIAS(s[0].f1, s[1].f2);
	TBHC_NOALIAS(p[1], s[1].f1);

	if (a)
		s[1].f1 = &c;
	TBHC_MAYALIAS(s[0].f1, s[1].f2);

	return 0;
}
