#include <stdio.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);

#define LEN 3

int main() {
    int *arr[LEN];

    for (int i = 0; i < LEN; i++)
    {
        arr[i] = malloc(sizeof(int));
        if (arr[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        *arr[i] = 0;
    }

    for (int j = 0; j < LEN; j++)
    {
        SAFE_LOAD(&arr[j]);
    }

    return 0;
}
