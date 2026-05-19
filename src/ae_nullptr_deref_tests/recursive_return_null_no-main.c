#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

int *recursive_function(int depth) {
    if (depth > 0) {
        // Do nothing and keep calling itself
        recursive_function(depth - 1);
    } else {
        // Base case reached, dereferencing NULL pointer
        return NULL;
    }
}

int no_main_recursive_return_null() {
    int *intPtr = recursive_function(5);

    UNSAFE_LOAD(intPtr);
    
    return 0;
}