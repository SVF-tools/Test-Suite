#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

char *getNullPointer() {
    return NULL;  // Function returns a NULL pointer
}

int main() {
    char *ptr = getNullPointer();

    UNSAFE_LOAD(ptr);

    return 0;
}
