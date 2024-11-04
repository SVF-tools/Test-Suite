#include <stdio.h>

extern void SAFE_LOAD(void *ptr);

void recursive_function(void *ptr, int depth) {
    if (depth > 0) {
        // Do nothing and keep calling itself
        recursive_function(ptr, depth - 1);
    } else {
        // Base case reached
        SAFE_LOAD(ptr); 
    }
}

int main() {
    int *intPtr = malloc(sizeof(int));
    char *charPtr = malloc(sizeof(char));
    recursive_function(intPtr, 3);
    recursive_function(charPtr, 3);
    
    return 0;
}