#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);

void foo(int *a) {
    SAFE_LOAD(a);
}

int main() {
    int* p = malloc(sizeof(int));
    *p = 1;
    foo(p);
}
