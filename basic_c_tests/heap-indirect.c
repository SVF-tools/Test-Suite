/*
 * Heap
 * Author: Sen Ye
 * Date: 12/10/2013
 * Description: heap objects are identified according to their
 *		allocation sites.
 */
#include "aliascheck.h"

// return two malloc object
void malloc_two(int **p, int **q) {
	*p = (int*) malloc(sizeof(int));
	*q = (int*) malloc(sizeof(int));
}

int main() {
	int **o1 = malloc(100);
    int **o2 = malloc(100);
	malloc_two(o1, o2);
	NOALIAS(*o1, *o2);
	return 0;
}
