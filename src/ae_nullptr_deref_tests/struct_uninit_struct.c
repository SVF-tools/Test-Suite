#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

struct Data {
    int number;
    char character;
};

int main() {
    struct Data *dataPtr;

    UNSAFE_LOAD(&dataPtr->number);  // Accessing a member of the structure via NULL pointer
    UNSAFE_LOAD(&dataPtr->character);

    return 0;
}
