#include <stdlib.h>
#include "stdbool.h"
extern void svf_assert(bool);

int no_main_INTERVAL_test_6_0() {
	int a = 0;
    while(a < 10) {
        a++;
    }
    svf_assert(a == 10);    
}