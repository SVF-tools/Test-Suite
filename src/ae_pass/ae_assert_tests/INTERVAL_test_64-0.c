#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <stdbool.h>

void increment(int* a) {
	*a = *a + 1;
}

int recursive(int a) {
	a--;
	if(a) {
		a = recursive(a);
	}
	return a;
}

int main() {
	int a;
	LOOP:
	if(a > 5) {
		a--;
	}
	else if(a < 5) {
		a++;
	}
	
	if(a != 5) {
		goto LOOP;
	}
	else {
		a = recursive(a);
	}
	while(true) {
		increment(&a);
		if(a == 10) {
			exit(0);
		}
	}
}