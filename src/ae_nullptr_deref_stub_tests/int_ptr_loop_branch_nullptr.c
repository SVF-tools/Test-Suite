#include <stdio.h>
#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {
    int *p;
    int i = 0;
    while (i < 100) {
        if (i == 50) {
            p = NULL;
        }
        else {
            p = malloc(sizeof(int));
        }
        UNSAFE_LOAD(p);
        i++;
    }

    return 0;
}
