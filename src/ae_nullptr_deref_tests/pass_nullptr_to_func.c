#include <stdio.h>

void foo(int *ptr) {
    printf("Value: %d\n", *ptr);  // Dereferencing the NULL pointer
}

int main() {
    int *ptr = NULL;

    foo(ptr);  // Passing a NULL pointer to the function

    return 0;
}
