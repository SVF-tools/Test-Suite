#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int no_main_INTERVAL_test_58_0() {
	int a;
	int b;
	if(a >= 0) {
		do {
		    printf("%d\n", a);
			for(int i = b; i > a; i--) {
				if(i % 2 == 0) {
					printf("%d is even\n", i);
				}
				else {
					printf("%d is odd\n", i);
				}
			}
			a--;
		} while(a);
	}
}