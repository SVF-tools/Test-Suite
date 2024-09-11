#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

struct Data {
    int number;
    char character;
};

int main() {
    struct Data *dataPtr = NULL;

    UNSAFE_LOAD(dataPtr->number);  // Accessing a member of the structure via NULL pointer

    return 0;
}
