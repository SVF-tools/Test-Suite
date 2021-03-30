/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"

struct MyStruct {
	int * f1;
	int * f2;
};

int main() {
	struct MyStruct s[3];
	int a,b,c,d;
	s[0].f1 = &a, s[0].f2 = &c;//, s[0].f3 = &x;
	s[1].f1 = &b, s[1].f2 = &d;//, s[1].f3 = &y;

	if (a)
		s[1].f1 = &c;
	TBHC_MAYALIAS(s[0].f1, s[1].f2);

	return 0;
}
