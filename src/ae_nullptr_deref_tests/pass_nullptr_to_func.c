#include <stdio.h>

void printValue(int *ptr) {
    printf("Value: %d\n", *ptr);  // Dereferencing the NULL pointer
}

int main() {
    int *ptr = NULL;

    printValue(ptr);  // Passing a NULL pointer to the function

    return 0;
}
