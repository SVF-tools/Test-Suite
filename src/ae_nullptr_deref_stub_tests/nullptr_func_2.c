#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);
typedef void (*FuncPtr)();  // Define a function pointer type

void invokeFunction(FuncPtr func) {
    UNSAFE_LOAD(func);
}

int main() {
    FuncPtr funcPtr = NULL;  // Initialize function pointer to NULL

    invokeFunction(funcPtr);  // Attempt to call the function via the NULL pointer

    return 0;
}