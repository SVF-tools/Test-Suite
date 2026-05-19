#include <stdlib.h>
#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);

int no_main_INTERVAL_test_8_0() {
	int a = rand();
    while(a < 10) {
        a++;
    }
    svf_print(a, "a");
    svf_assert(a >= 10);
}