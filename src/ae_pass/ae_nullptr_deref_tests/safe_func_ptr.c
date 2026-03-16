#include <stdio.h>

void testFunction() {
    printf("Test function called\n");
}

int main() {
    void (*funcPtr)();
    funcPtr = testFunction;
    SAFE_LOAD(&funcPtr);
    funcPtr();

    return 0;
}