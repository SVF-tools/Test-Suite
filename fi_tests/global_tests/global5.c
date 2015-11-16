/*
 * Global variables test.
 * Author: Sen Ye
 * Date: 07/05/2014
 */
#include "aliascheck.h"

typedef unsigned char *POINTER;

struct MyStruct {
	int* f1;
	unsigned char f2[64];
};

struct MyStruct context;

static unsigned char padding[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static void memcpy(POINTER output, POINTER input, unsigned long len)
{
	unsigned long i;
	for (i=0; i<len; i++)
		output[i] = input[i];
}

void update(struct MyStruct* context, unsigned char* input, unsigned long length)
{
	int index;
	memcpy((POINTER)&context->f2[index], (POINTER)input, length);
}

int main()
{
	int l;
	update(&context, padding, l);
	return 0;
}
