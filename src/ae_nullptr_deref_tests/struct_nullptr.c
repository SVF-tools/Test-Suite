#include <stdio.h>

struct Data {
    int number;
    char character;
};

int main() {
    struct Data *dataPtr = NULL;

    int num = dataPtr->number;  // Accessing a member of the structure via NULL pointer

    return 0;
}
