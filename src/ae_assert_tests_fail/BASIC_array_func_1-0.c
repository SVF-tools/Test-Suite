//
// Created by Jiawei Wang on 2/3/22.
//

#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);

int getValue(int** arr, int x, int y) {
    return arr[x][y];
}

int main() {
    int arr[2][2];
    arr[0][0] = 10;
    int v = getValue(arr, 0, 0);
    svf_print(v, "value");
    svf_assert(v == 10);
    return 0;
}