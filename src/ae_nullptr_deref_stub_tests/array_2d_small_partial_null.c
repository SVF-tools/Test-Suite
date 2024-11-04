#include <stdio.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);
extern void UNSAFE_LOAD(void *ptr);

int main() {
    int *arr[2][2];
    arr[0][0] = NULL;
    arr[0][1] = NULL;
    arr[1][0] = malloc(sizeof(int));
    arr[1][1] = malloc(sizeof(int));

    *arr[1][0] = 123;
    *arr[1][1] = 456;

    UNSAFE_LOAD(arr[0][0]);
    UNSAFE_LOAD(arr[0][1]);
    SAFE_LOAD(arr[1][0]);
    SAFE_LOAD(arr[1][1]);
}