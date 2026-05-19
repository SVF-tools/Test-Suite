#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

int no_main_array_2d_small() {
    int *arr[2][2];
    arr[0][0] = NULL;
    arr[0][1] = NULL;
    arr[1][0] = NULL;
    arr[1][1] = NULL;

    UNSAFE_LOAD(arr[0][0]);
    UNSAFE_LOAD(arr[0][1]);
    UNSAFE_LOAD(arr[1][0]);
    UNSAFE_LOAD(arr[1][1]);
}