//
// Created by Ethan Lin on 21/10/2024.
//
#include <stdlib.h>

extern void SAFE_LOAD(void *p);
extern void UNSAFE_LOAD(void *p);
//extern void svf_assert(bool);

int main() {
    int *myPtr = (int*)malloc(sizeof(int));
    free(myPtr);
    UNSAFE_LOAD(myPtr);
    myPtr = (int*)malloc(sizeof(int));
    *myPtr = 200;
    SAFE_LOAD(myPtr);
    return 0;
}

