//
// Created by Jiawei Wang on 1/16/22.
//

#include "stdbool.h"
//ADDR, LOAD, STORE, CAST(COPY)
extern void svf_assert(bool);

int no_main_BASIC_ptr_assign_0_0() {
    int *p;
    int a = 1;
    p = &a;
    *p = 3;
    svf_assert(a == 3);
}
