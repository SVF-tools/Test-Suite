#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int recursive(int a) {
	a--;
	if(a) {
		a = recursive(a);
	}
	return a;
}

int main() {
	int a;
	if(a > 0) {
		a = recursive(a);
	}
	else {
		a = recursive(abs(a));
	}
	svf_assert(a == 0);
}
