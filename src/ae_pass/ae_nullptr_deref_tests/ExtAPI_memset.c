#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);
extern void UNSAFE_LOAD(void *ptr);

void test_safe_memset() {
    int *a = (int *)malloc(5 * sizeof(int));
    if (a) {
        SAFE_LOAD(a);
        memset(a, 0, 5 * sizeof(int));  // Safe memset of 5 integers
    }
    free(a);
}

void test_unsafe_memset() {
    int *a = NULL;

    UNSAFE_LOAD(a);  // a is NULL — unsafe

    memset(a, 0, 5 * sizeof(int));  // Undefined behavior
}

int main() {
    test_safe_memset();
    test_unsafe_memset();  // Likely crash
    return 0;
}
