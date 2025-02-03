#include <stdio.h>
#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {
    int *arr[5];
    arr[0] = malloc(sizeof(int));
    arr[1] = malloc(sizeof(int));
    arr[2] = malloc(sizeof(int));
    arr[3] = malloc(sizeof(int));

    arr[4] = NULL;

    for (int i = 0; i < 5; i++)
    {
        UNSAFE_LOAD(arr[i]);
    }

    return 0;
}
