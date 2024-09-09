#include <stdio.h>

int main() {    
    
    int *ptrs[5] = {NULL, NULL, NULL, NULL, NULL};
    for (int i = 0; i < 5; i++) {
        int value = *ptrs[i];  // Triggers null pointer dereference
    }

    return 0;
}