#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

char *getNullPointer() {
    return NULL;  // Function returns a NULL pointer
}

char *foo() {
    char *p = getNullPointer();
    return p;
}

int main() {
    char *ptr = foo();

    UNSAFE_LOAD(ptr);  // Dereferencing the NULL pointer

    return 0;
}
