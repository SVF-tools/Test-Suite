#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

struct Data {
    int number;
    char character;
};

int main() {
    struct Data *dataPtr = NULL;

    UNSAFE_LOAD(dataPtr);  // Accessing a member of the structure via NULL pointer
    dataPtr->number = 0;

    return 0;
}
