//
// Created by Jiawei Wang on 1/20/22.
//
#include "stdbool.h"

extern void svf_assert(bool);
int no_main_BASIC_assign_0_0() {
    int a = -1;
    a = a*a;
    svf_assert(a>0);
    return 0;
}
