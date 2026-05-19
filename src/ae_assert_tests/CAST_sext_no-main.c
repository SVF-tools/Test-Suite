#include "stdbool.h"
extern void svf_assert(bool);

int no_main_CAST_sext() {
    signed char size = -1;
    int c = size;
    svf_assert(c == -1);
}