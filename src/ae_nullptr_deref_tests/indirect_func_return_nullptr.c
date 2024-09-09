#include <stdio.h>

int *getNullPointer() {
    return NULL;  // Function returns a NULL pointer
}

int *foo() {
    int *p = getNullPointer();
    return p;
}

int main() {
    int *ptr = foo();

    int value = *ptr;  // Dereferencing the NULL pointer

    return 0;
}
