#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {
    char *ptr = NULL;

    char *newPtr = ptr + 5;  // Perform pointer arithmetic on NULL pointer

    UNSAFE_LOAD(newPtr);  // Dereference the result

    return 0;
}
