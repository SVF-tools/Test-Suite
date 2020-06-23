/*
 * Struct casting.
 * Author: Sen Ye
 * Date: 28/04/2014
 */
#include "aliascheck.h"

struct InnerStruct {
	char in1;
	int* in2;
};

struct SrcStruct {
	int* f1[10];
	char f2[10];
	struct InnerStruct f3[5];
	char f4;
};

struct DstStruct {
	int* f1[10];
	char f2[20];
	struct InnerStruct f3[5];
};

int main() {
	struct DstStruct* pdst;
	struct SrcStruct* psrc;
	struct SrcStruct s;
	int x, y, z;

	psrc = &s;
	psrc->f1[3] = &x;
	psrc->f3[2].in2 = &y;

	pdst = psrc;

	MAYALIAS(pdst->f1[9], &x);
	MAYALIAS(pdst->f3[3].in2, &y);
	NOALIAS(psrc->f1[2], &z);

	pdst->f3[1].in2 = &z;
	MAYALIAS(psrc->f3[1].in2, &z);

	return 0;
}
