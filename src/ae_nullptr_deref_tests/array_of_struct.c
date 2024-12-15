#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);
extern void UNSAFE_LOAD(void *ptr);

struct S {
    int *intPtr;
};

int main() {    
    struct S arrStruct[3];

    arrStruct[0].intPtr = malloc(sizeof(int));
    *arrStruct[0].intPtr = 1024;

    arrStruct[1].intPtr = NULL;

    SAFE_LOAD(arrStruct[0].intPtr);     // malloc
    UNSAFE_LOAD(arrStruct[1].intPtr);   // NULL
    UNSAFE_LOAD(arrStruct[2].intPtr);   // uninitialized

    return 0;
}