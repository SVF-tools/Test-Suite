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

    SAFE_LOAD(dataPtr);
    /*
        This failed because dataPtr's addr (e.g 0x...6a) is not in _addrToAbsVal
        store on dataPtr->number => gep(dataPtr, 0) => generate a new addr (e.g 0x...ee) to store in _addrToAbsVal
        Therefore, only (0x...ee) is in _addrToAbsVal but not (0x...6a)
    */

    return 0;
}
