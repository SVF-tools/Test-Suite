#include "stdbool.h"
extern void svf_assert(bool);
int no_main_BASIC_assign_2_0() {
    int a = 10;
    int b = 5;
    a = b;
    svf_assert( a != 10);
    return 0;
}