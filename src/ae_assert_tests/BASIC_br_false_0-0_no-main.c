
// CHECK: ^sat$


#include "stdbool.h"

extern void svf_assert(bool);

int no_main_BASIC_br_false_0_0() {
    int x;
    x = 1;

    if (false) {
        x++;
    }
    svf_assert(x != 2);
    return 0;
}