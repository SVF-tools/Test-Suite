//
// Created by Jiawei Wang on 1/27/22.
//


#include "stdbool.h"
extern void svf_assert(bool);

struct {
    int a;
    int b;
}typedef A;
int main() {
    A a[2];
    a[0].a = 10;
    a[0].b = 11;
    a[1].a = 20;
    a[1].b = 21;
    int c = 0;
    svf_assert(a[c].b == 11);
    return 0;
}