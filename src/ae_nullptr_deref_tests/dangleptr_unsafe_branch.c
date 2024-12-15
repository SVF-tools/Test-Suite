//
// Created by Ethan Lin on 11/11/2024.
//

#include <stdlib.h>

extern void SAFE_LOAD(void *p);
extern void UNSAFE_LOAD(void *p);

int main() {
    int a = 5;

    int *myPtr;

    myPtr = (int*)malloc(sizeof(int));
    free(myPtr);
    UNSAFE_LOAD(myPtr);
    if (a < 0)
    {
        myPtr = &a;
    } else
    {
        /* Do nothing */
    }
    
    UNSAFE_LOAD(myPtr);
    return 0;
}
