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
    *myPtr = 404;    // trigger NPD

    int x = 200;
    myPtr = &x;
    svf_assert(*myPtr == 200);

    SAFELOAD(myPtr);


    return 0;
}

