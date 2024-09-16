#include <stdio.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);

#define LEN 10

int main() {
    int *arr[LEN] = {};

    for (int i = 0; i < LEN; i++)
    {
        arr[i] = malloc(sizeof(int));
        *arr[i] = 0;
    }

    for (int j = 0; j < LEN; j++)
    {
        int *p = arr[j];
        SAFE_LOAD(p);
    }

    return 0;
}
