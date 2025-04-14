//
// Created by Ethan Lin on 21/10/2024.
//
#include <stdlib.h>

extern void SAFE_LOAD(void *p);

int main() {
    int *myPtr = malloc(sizeof(int));
    *myPtr  = 123;
    SAFE_LOAD(myPtr);
    return 0;
}

