#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <stdbool.h>
#include <math.h>

int a;

int foo(int input) {
	int output = 0;
	for(int i = 0; i < input; i++) {
		output++;
	}
	return output;
}

int main() {
    a = rand();
    int b = a;
	if(a > 0) {
		for(int i = 0; i < b; i++) {
			a = a + foo(a);
		}
	    svf_assert(a == b * pow(2, b));
	}
	while(true) {
		LOOP:
		a -= pow(2, b);
		if(a) {
			goto LOOP;
		}
		exit(0);
	}
}
