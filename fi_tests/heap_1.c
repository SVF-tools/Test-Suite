/*
 * Heap
 * Author: Sen Ye
 * Date: 12/10/2013
 * Description: heap objects are identified according to their
 *		allocation sites.
 */
#include "aliascheck.h"

// return one malloc object
int * my_alloc() {
	int * p = (int *) malloc(sizeof(int));
	return p;
}

int main() {
	int * o1 = my_alloc();
	int * o2 = my_alloc();
	MAYALIAS(o1, o2);
	return 0;
}
