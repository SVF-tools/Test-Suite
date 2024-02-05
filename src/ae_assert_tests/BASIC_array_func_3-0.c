//
// Created by Jiawei Wang on 2/3/22.
//

#include "stdbool.h"
extern void svf_assert(bool);

struct {
    int a;
    int b[2];
}typedef A;

int getValue(A* arr, int x) {
    return arr->b[x];
}

int main() {
    A a;
    a.a = 0;
    a.b[0] = 1;
    a.b[1] = 2;
    svf_assert(getValue(&a, 1) == 2);
    return 0;
}