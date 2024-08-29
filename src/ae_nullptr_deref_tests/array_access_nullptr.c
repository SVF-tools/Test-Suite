#include <stdio.h>

int main() {
    int *ptr = NULL;

    int value = ptr[5];  // Attempting to access an array element via NULL pointer

    return 0;
}
