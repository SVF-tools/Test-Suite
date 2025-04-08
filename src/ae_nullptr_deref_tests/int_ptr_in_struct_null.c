//
// Created by Ethan Lin on 30/9/2024.
//

#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

struct S {
    int *ptr;
};

int main() {
    struct S myStruct;
    myStruct.ptr = NULL;

    UNSAFE_LOAD(myStruct.ptr);
    *myStruct.ptr = 404;

    return 0;
}
