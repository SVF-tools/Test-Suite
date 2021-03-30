/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"

struct MyStruct {
	int *f1;
	int *f2;
};

int main() {
	struct MyStruct s[2];
	int x, y;
	s[0].f1 = &x;
	s[1].f2 = &y;

	s[0].f1 = &y;
	TBHC_MUSTALIAS(s[0].f1, s[1].f2);
	return 0;
}
