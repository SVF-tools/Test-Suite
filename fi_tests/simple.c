/*
 * Simple alias check
 * Author: Sen Ye
 * Date: 06/09/2013
 */
#include "aliascheck.h"

int main()
{
	int a,b,*c,*d;
	c = &a;
	d = &a;
	MUSTALIAS(c,d);
	c = &b;
	// In LLVM, top level variables
	// will be converted into SSA, so
	// different versions should have
	// different values.
	NOALIAS(c,d);
	return 0;
}
