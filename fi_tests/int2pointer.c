/*
 * Alias due to casting between
 * integer and pointer.
 * Author: Sen Ye
 * Date: 06/09/2013
 */

#include "aliascheck.h"

struct MyStruct {
	int f1;
	int f2;
};

int main() {
	struct MyStruct ms;
	int *p, *q;
	p = &(ms.f1);
	// cast pointer to integer
	int addr = (int)p;
	// cast integer to pointer and
	// q would point to blackhole
	q = (int*)addr + 1;
	EXPECTEDFAIL_MAYALIAS(p, q);
	return 0;
}
