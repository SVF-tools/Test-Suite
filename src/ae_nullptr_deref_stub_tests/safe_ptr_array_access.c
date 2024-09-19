#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);

int main() {    
    int *n = malloc(sizeof(int));
    *n = 0;
    int *ptrs[5] = {n, n, n, n, n};
    for (int i = 0; i < 5; i++) {
        SAFE_LOAD(ptrs[i]);
        *ptrs[i] = 1;
    }

    return 0;
}