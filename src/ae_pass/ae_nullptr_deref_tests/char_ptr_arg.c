#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

void foo(char *ptr) {
    UNSAFE_LOAD(ptr);  // Dereferencing the NULL pointer
}

int main() {
    char *ptr = NULL;

    foo(ptr);  // Passing a NULL pointer to the function

    return 0;
}
