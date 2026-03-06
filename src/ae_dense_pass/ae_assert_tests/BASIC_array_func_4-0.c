//
// Created by Jiawei Wang on 2/5/22.
//


#include "stdbool.h"
extern void svf_assert(bool);

int getValue(int* arr, int x) {
    return arr[x];
}

int main() {
    int arr[2];
    arr[0] = 0;
    arr[1] = 1;
    int res = getValue(arr, 1);
    svf_assert(res == 1);
    return 0;
}