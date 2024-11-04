#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr[5];
    arr[0] = malloc(sizeof(int));
    arr[1] = malloc(sizeof(int));
    arr[2] = malloc(sizeof(int));
    arr[3] = malloc(sizeof(int));

    arr[4] = NULL;

    for (int i = 0; i < 5; i++)
    {
        *arr[i] = i;
    }

    return 0;
}
