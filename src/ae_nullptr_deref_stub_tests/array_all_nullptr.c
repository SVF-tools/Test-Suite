#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {    
    int *n = NULL;
    int *ptrs[5] = {n, n, n, n, n};
    for (int i = 0; i < 5; i++) {
        UNSAFE_LOAD(ptrs[i]);
    }

    return 0;
}