#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);

int *foo() {
    int* p = malloc(sizeof(int));
    *p = 1;
    return p;
}

int main() {
    int *myPtr = foo();
    SAFE_LOAD(myPtr);
}
