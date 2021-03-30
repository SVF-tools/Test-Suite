/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"

struct MyStruct {
	int *f1;
	int *f2;
};

int main() {
	struct MyStruct s1, s2;
	int x, y;
	s1.f1 = &x;
	s1.f2 = &y;
	s2.f1 = &y;
	s2.f2 = &x;
	TBHC_NOALIAS(s1.f1, s1.f2);
	TBHC_NOALIAS(s1.f1, s2.f1);

	s1.f1 = &y;
	TBHC_MUSTALIAS(s1.f1, s2.f1);
	return 0;
}
