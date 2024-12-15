#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

int* getNullPointer() {
    return NULL;  // Function returns a NULL pointer
}

int main() {
    int *ptr = getNullPointer();

    UNSAFE_LOAD(ptr);

    return 0;
}
