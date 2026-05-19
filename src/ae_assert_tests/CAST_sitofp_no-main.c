#include "stdbool.h"
extern void svf_assert(bool);
int no_main_CAST_sitofp() {
    int si = -42;
    float f = (float)si; // sitofp
    svf_assert(f == -42.0f);
    return 0;
}