#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

void recursive_function(void *ptr, int depth) {
    if (depth > 0) {
        // Do nothing and keep calling itself
        recursive_function(ptr, depth - 1);
    } else {
        // Base case reached, dereferencing NULL pointer
        UNSAFE_LOAD(ptr);  // This will trigger a null pointer dereference
    }
}

int main() {
    int *intPtr = NULL;
    char *charPtr = NULL;
    recursive_function(intPtr, 1);
    recursive_function(charPtr, 1);
    
    return 0;
}