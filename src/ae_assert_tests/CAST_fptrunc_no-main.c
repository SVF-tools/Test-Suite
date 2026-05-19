#include "stdbool.h"
extern void svf_assert(bool);
int no_main_CAST_fptrunc() {
    double d = 1.0;
    float f = (float)d; // fptrunc from double to float
    svf_assert(f == 1.0f);
    return 0;
}