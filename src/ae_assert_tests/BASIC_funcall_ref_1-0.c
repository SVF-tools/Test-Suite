//
// Created by Jiawei Wang on 12/30/21.
//
#include "stdbool.h"
//ADDR, LOAD, STORE, CAST(COPY)
extern void svf_assert(bool);

void swap(int* p, int* q) {
    int t = *p;
    *p = *q;
    *q = t;
}

int main() {
   int a = 0, b = 1;
    swap(&a, &b);
    svf_assert(a == 1);
}
