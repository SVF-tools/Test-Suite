//
// Created by Ethan Lin on 21/10/2024.
//
#include <stdlib.h>

extern void SAFE_LOAD(void *p);
extern void UNSAFE_LOAD(void *p);

int main() {
    int x = 6;
    int *myPtr2;
    myPtr2 = &x;
    SAFE_LOAD(myPtr2);
    *myPtr2 = 5;

    return 0;
}

