#include <stdio.h>

int* getNullPointer() {
    return NULL;  // Function returns a NULL pointer
}

int main() {
    int *ptr = getNullPointer();

    int value = *ptr;  // Dereferencing the NULL pointer

    printf("Value: %d\n", value);  // This line may cause a crash

    return 0;
}
