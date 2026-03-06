#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {
    int* p = malloc(sizeof(int));
    *p = 1;
    free(p);
    p = NULL;
    UNSAFE_LOAD(p);
}
