/*
 * Testcases from 254.gap.
 * Author: Sen Ye
 * Date: 12/05/2014
 */
#include <stdlib.h>
#include "aliascheck.h"

/// Note that `SyGetmem` is summarized lib function (with side-effect ExtAPI::EFT_ALLOC) in ExtAPI.cpp, we will use SVF's summmary instead of this user defined function
char *  SyGetmem ( long size );

typedef struct TypHeader {
	struct TypHeader    * * ptr;
}    * TypHandle;

TypHandle HdFree;
TypHandle FreeHandle;
TypHandle* FirstBag;

void IntComm () {}

TypHandle NewBag() {
	long needed;
	TypHandle *d, *s, *e;
	TypHandle h;

	d = ((TypHandle*)((HdFree)->ptr)) + needed / (sizeof(TypHandle)) - 1;
	s = ((TypHandle*)((HdFree)->ptr)) - 1;
	e = (FirstBag-1);
	while ( e <= s )  *d-- = *s--;
	MAYALIAS(*s, &IntComm);

	for (h=HdFree; h < (TypHandle)(FirstBag-1); ++h)
		h->ptr += needed / (sizeof(TypHandle));

	h->ptr = (TypHandle*)FreeHandle;
	FreeHandle = h;

	return FreeHandle;
}

void InstIntFunc(void (*func)()) {
	TypHandle hdDef = NewBag();
	*(void(**)())((TypHandle*)((hdDef)->ptr)) = func;
}

void InitGasman() {
	long SyMemory;
	HdFree = (TypHandle)SyGetmem( SyMemory );
	FreeHandle = (TypHandle)((TypHandle*)((FreeHandle)->ptr));
}

int main() {
	InitGasman();
	InstIntFunc(IntComm);
	return 0;
}
