#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

void recursive_function(int *ptr, int depth) {
    if (depth > 0) {
        // Do nothing and keep calling itself
        recursive_function(ptr, depth - 1);
    } else {
        // Base case reached, dereferencing NULL pointer
        UNSAFE_LOAD(ptr);  // This will trigger a null pointer dereference
    }
}

int main() {
    int *ptr = NULL;
    recursive_function(ptr, 3);
    return 0;
}