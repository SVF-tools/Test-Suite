#include <stdio.h>
#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {
    char *ptr = (char *)malloc(sizeof(char));  // Allocate memory

    int a = 0;

    if (a >= 0) {
        ptr = NULL;
    }

    UNSAFE_LOAD(ptr);

    return 0;
}
