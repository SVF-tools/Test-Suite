//
// Created by Ethan Lin on 21/10/2024.
//
#include <stdlib.h>

extern void SAFE_LOAD(void *p);
extern void UNSAFE_LOAD(void *p);
//extern void svf_assert(bool);

int main() {
    int *myPtr;
    free(myPtr);
    UNSAFE_LOAD(myPtr);
    return 0;
}

