/*
 * Simple program to test flow-sensitive analysis.
 * Author: Sen Ye
 * Date: 12/11/2013
 */

#include "aliascheck.h"
#include <stdlib.h>

int * my_malloc(int * q) {
	int *p = malloc(*q);
	return p;
}

int main() {
	int *p, q;
	p = my_malloc(&q);
	return 0;
}
