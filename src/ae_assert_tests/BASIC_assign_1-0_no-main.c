#include "stdbool.h"
extern void svf_assert(bool);
int no_main_BASIC_assign_1_0(){
    int x=1;
    int y=1;
    svf_assert(x == y);
    return 0;
}