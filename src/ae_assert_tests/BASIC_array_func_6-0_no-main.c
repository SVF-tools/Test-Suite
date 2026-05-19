//
// Created by Jiawei Wang on 2/3/22.
//

#include "stdbool.h"
extern void svf_assert(bool);

int getValue(int arr[2][2], int x, int y) {
    return arr[x][y];
}

int no_main_BASIC_array_func_6_0() {
    int arr[2][2];
    arr[0][0] = 10;
    int v = getValue(arr, 0, 0);
    svf_assert(v == 10);
    return 0;
}