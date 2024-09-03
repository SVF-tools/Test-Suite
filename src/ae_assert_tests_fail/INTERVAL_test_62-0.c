#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <stdbool.h>

int main() {
	int a;
	while(true) {
		if(a) {
			svf_assert(a != 0);
			abort();
		}
		else {
			if(a > 0) {
				a--;
			}
			else {
				a++;
			}
			continue;
		}
	}
}
