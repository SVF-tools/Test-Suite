#include "stdbool.h"
extern void svf_assert(bool);
int no_main_BASIC_bi_add_1_0() {
    int a, b;
    a = 1;
    a += 2 ;
    b = a;
    svf_assert( b == 3 );
    return 0;
}