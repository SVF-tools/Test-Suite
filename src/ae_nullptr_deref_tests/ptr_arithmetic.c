#include <stdio.h>

int main() {
    int *ptr = NULL;

    int *newPtr = ptr + 5;  // Perform pointer arithmetic on NULL pointer

    int value = *newPtr;  // Dereference the result

    printf("Value: %d\n", value);  // This line may cause a crash

    return 0;
}
