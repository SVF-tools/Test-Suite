#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

void foo(int *ptr) {
    UNSAFE_LOAD(ptr);  // Dereferencing the NULL pointer
}

int main() {
    int *ptr = NULL;

    foo(ptr);  // Passing a NULL pointer to the function

    return 0;
}
