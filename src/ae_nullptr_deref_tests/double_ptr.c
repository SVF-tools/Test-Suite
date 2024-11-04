#include <stdio.h>

int main() {    
    
    int **double_ptr = NULL;
    int value = **double_ptr;  // This will trigger a null pointer dereference

    return 0;
}