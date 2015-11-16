/*
 * Struct with array.
 * Author: Sen Ye
 * Date: 28/04/2014
 */
#include "aliascheck.h"

struct ArrayStruct {
	int f1;
	char f2;
	int f3[100];
	int f4;
};

int main() {
	struct ArrayStruct* p;
	struct ArrayStruct s;
	int* q;

	p = &s;
	q = &s.f3[40];
	MAYALIAS(&p->f3[10], q);
	MAYALIAS(&p->f3[20], &p->f3[30]);
	MAYALIAS(&s.f3[0], &s.f3[99]);
	NOALIAS(&p->f3[0], &s.f4);
	
	return 0;
}
