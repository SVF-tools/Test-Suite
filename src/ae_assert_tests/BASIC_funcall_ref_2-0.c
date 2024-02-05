//
// Created by Jiawei Wang on 12/30/21.
//
#include "stdbool.h"
//ADDR, LOAD, STORE, CAST(COPY)
extern void svf_assert(bool);

int foo(int* p) {
  return 0;
}

int main() {
    int a = 0;
    int res = foo(&a);
    svf_assert(res == 0);
}
