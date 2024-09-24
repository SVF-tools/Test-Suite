#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {
    char *p = malloc(sizeof(char) * 100);
    *p = 'This string can be stored.';
    free(p);
    p = NULL;
    UNSAFE_LOAD(p);
}
