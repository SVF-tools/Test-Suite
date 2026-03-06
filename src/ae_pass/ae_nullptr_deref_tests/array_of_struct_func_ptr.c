#include <stdlib.h>
#include <stdio.h>

extern void SAFE_LOAD(void *ptr);
extern void UNSAFE_LOAD(void *ptr);

struct S {
    void (*funcPtr)();
};

void foo() {
    printf("This is a function\n");
}

int main() {    
    struct S arrStruct[3];

    arrStruct[0].funcPtr = &foo;

    arrStruct[1].funcPtr = NULL;

    SAFE_LOAD(arrStruct[0].funcPtr);     // malloc
    UNSAFE_LOAD(arrStruct[1].funcPtr);   // NULL
    UNSAFE_LOAD(arrStruct[2].funcPtr);   // uninitialized

    return 0;
}