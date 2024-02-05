#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

int main() {
	int a;
	int b = MIN(a * a * a, a);
	if(b == a) {
		svf_assert(a >= 0);
	}
	else {
		svf_assert(a < 0);
	}
}