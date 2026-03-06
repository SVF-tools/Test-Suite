#include <stdio.h>
#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {
    int *ptr = (int *)malloc(sizeof(int));  // Allocate memory

    int a = 0;

    if (a >= 0) {
        ptr = NULL;
    }

    UNSAFE_LOAD(ptr);

    return 0;
}
