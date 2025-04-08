#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

int *getNullPointer() {
    return NULL;  // Function returns a NULL pointer
}

int *foo() {
    int *p = getNullPointer();
    return p;
}

int main() {
    int *ptr = foo();

    UNSAFE_LOAD(ptr);  // Dereferencing the NULL pointer

    return 0;
}
