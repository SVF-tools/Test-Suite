/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"

struct MyStruct {
	int * f1;
	int * f2;
};

int main() {
	struct MyStruct s[2];
	int a,b,c,d;
	s[0].f1 = &a, s[0].f2 = &c;//, s[0].f3 = &x;

	if (a)
		s[1].f1 = &c;
	TBHC_MAYALIAS(s[0].f1, s[1].f2);
	return 0;
}
