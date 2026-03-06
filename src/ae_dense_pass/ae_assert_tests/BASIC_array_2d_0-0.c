//
// Created by Jiawei Wang on 1/27/22.
//

#include "stdbool.h"
extern void svf_assert(bool);

int main() {
    int a[3][3];
    a[0][0] = 0;
    a[0][1] = 1;
    a[0][2] = 2;
    a[1][0] = 3;
    a[1][1] = 4;
    a[1][2] = 5;
    a[2][0] = 6;
    a[2][1] = 7;
    a[2][2] = 8;

    int b = 2, c = 2;
    svf_assert(a[b][c] == 8);
    return 0;
}