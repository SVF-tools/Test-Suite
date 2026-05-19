#include <stdlib.h>
#include "stdbool.h"
#include "math.h"
extern void svf_assert(bool);
extern void svf_assert_eq(int, int);

extern void svf_print(int, char*);
int no_main_wto_assert_02() {
	int a = rand();
    if (a > 5 && a < 7) {
        svf_print(a, "a value");
        svf_assert(a == 6);
    }
    else {
        // top
        int res = rand();
        svf_assert_eq(a, res);
    }
}