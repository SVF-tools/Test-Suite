//
// Created by Jiawei Wang on 12/30/21.
//
#include "stdbool.h"
//ADDR, LOAD, STORE, CAST(COPY)
extern void svf_assert(bool);

void foo(int* p) {
  *p = 1;
}

int no_main_BASIC_funcall_ref_0_0() {
    int a = 0;
    foo(&a);
    svf_assert(a == 1);
}
