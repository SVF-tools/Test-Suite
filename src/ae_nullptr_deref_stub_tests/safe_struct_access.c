#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);

struct Data {
    int number;
    char character;
};

int main() {
    struct Data *dataPtr = malloc(sizeof(struct Data));

    dataPtr->number = 0;
    dataPtr->character = 'a';

    SAFE_LOAD(&dataPtr->number);
    SAFE_LOAD(&dataPtr->character);

    return 0;
}
