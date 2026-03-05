//
// Created by Ethan Lin on 21/10/2024.
//
#include <stdlib.h>
#include <stdbool.h>

extern void SAFE_LOAD(void *p);
extern void UNSAFE_LOAD(void *p);
extern void svf_assert(bool cond);

int main() {
    int *safePtr = (int *)malloc(sizeof(int));
    *safePtr = 777;
    SAFE_LOAD(safePtr);

    free(safePtr);

    safePtr = (int *)malloc(sizeof(int)); 
    *safePtr = 888;
    SAFE_LOAD(safePtr);
    svf_assert(*safePtr == 888);

    return 0;
}

