#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {    
    
    char **double_ptr = NULL;
    UNSAFE_LOAD(double_ptr);  // This will trigger a null pointer dereference

    return 0;
}