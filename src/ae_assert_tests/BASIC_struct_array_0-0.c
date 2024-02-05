//
// Created by Jiawei Wang on 1/27/22.
//

#include "stdbool.h"
extern void svf_assert(bool);

struct {
    int a;
    int b[3];
}typedef A;
int main() {
    A a;
    a.b[0] = 4;
    a.b[1] = 5;
    a.b[2] = 6;
    a.a = 1;
    svf_assert(a.b[a.a] == 5);
    return 0;
}