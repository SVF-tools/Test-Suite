#include <stdlib.h>
#include "stdbool.h"
extern void svf_assert(bool);

int no_main_INTERVAL_test_11_0() {
	int a = 6;
    if (a > 5 && a < 7) {
        svf_assert(a == 6);
    }
    else {
        //svf_assert(a <= 5 || a >= 7);
    }
}