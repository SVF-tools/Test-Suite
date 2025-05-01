#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);
extern void UNSAFE_LOAD(void *ptr);

void test_safe_memcpy() {
    int *a = (int *)malloc(5 * sizeof(int));
    int *b = (int *)malloc(5 * sizeof(int));
    if (a && b) {
        for (int i = 0; i < 5; ++i) {
            b[i] = i;
        }

        SAFE_LOAD(a);
        SAFE_LOAD(b);

        memcpy(a, b, 5 * sizeof(int));  // Safe copy of 5 integers
    }
    free(a);
    free(b);
}

void test_unsafe_memcpy() {
    int *a = NULL;
    int *b = (int *)malloc(5 * sizeof(int));
    if (b) {
        for (int i = 0; i < 5; ++i) {
            b[i] = i;
        }

        UNSAFE_LOAD(a);  // a is NULL — unsafe
        SAFE_LOAD(b);  // b is valid

        memcpy(a, b, 5 * sizeof(int));  // Undefined behavior
    }
    free(b);
}

int main() {
    test_safe_memcpy();
    test_unsafe_memcpy();  // Likely crash
    return 0;
}
