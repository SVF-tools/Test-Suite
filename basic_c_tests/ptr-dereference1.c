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
	// In LLVM, every declared variable is address-taken 
	// accessed via pointers through loads/stores
	// c here is loaded from the same memory on LLVM's partial SSA form
	MAYALIAS(c,d);
	NOALIAS(&b,d);
	return 0;
}
