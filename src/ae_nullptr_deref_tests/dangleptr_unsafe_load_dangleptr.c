//
// Created by Ethan Lin on 21/10/2024.
//
#include <stdlib.h>

extern void SAFE_LOAD(void *p);
extern void UNSAFE_LOAD(void *p);

int main() {
    int *myPtr = (int*)malloc(sizeof(int));
    // SAFE_LOAD(myPtr);
    *myPtr = 200;
    free(myPtr);
    UNSAFE_LOAD(myPtr);
    *myPtr = 404;   // Trigger dangling pointer dereference
    return 0;
}

