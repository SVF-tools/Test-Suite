#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {
    void (*funcPtr)() = NULL;

    UNSAFE_LOAD(funcPtr);  // Attempting to call a function via a NULL function pointer

    return 0;
}