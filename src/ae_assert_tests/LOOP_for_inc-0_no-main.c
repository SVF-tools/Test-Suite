#include "stdbool.h"
extern void svf_assert(bool);

int no_main_LOOP_for_inc_0() {
    int i = 0;
    for (i = 0; i < 5; i++) {
        i++;
    }
    svf_assert(i >= 5 && i <= 6);
}
