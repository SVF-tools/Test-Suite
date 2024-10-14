#include <stdio.h>
int main() {
    void (*funcPtr)() = NULL;

    funcPtr();  // Attempting to call a function via a NULL function pointer

    return 0;
}