//
// Created by Jiawei Wang on 2/3/22.
//

#include "stdbool.h"
extern void svf_assert(bool);

struct {
    int a;
    int b;
}typedef A;

A getValue(A* arr, int x) {
    return arr[x];
}

int main() {
    A a[2];
    a[0].a = 10;
    a[0].b = 11;
    a[1].a = 20;
    a[1].b = 21;
    A res = getValue(a, 1);
    svf_assert(res.b == 21);
    return 0;
}