#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);
extern void UNSAFE_LOAD(void *ptr);

void test_safe_strcpy() {
    char *a = (char *)malloc(20);
    char *b = (char *)malloc(20);
    if (a && b) {
        strcpy(b, "Hello");

        // Safe usage
        SAFE_LOAD(a);
        SAFE_LOAD(b);

        strcpy(a, b);  // Copy b into a
    }
    free(a);
    free(b);
}

void test_unsafe_strcpy() {
    char *a = NULL;
    char *b = (char *)malloc(20);
    if (b) {
        strcpy(b, "Hello");

        // Unsafe usage
        UNSAFE_LOAD(a);  // a is NULL — unsafe
        SAFE_LOAD(b);  // b is valid

        strcpy(a, b);  // Undefined behavior (null dereference)
    }
    free(b);
}

int main() {
    test_safe_strcpy();
    test_unsafe_strcpy();  // This will likely crash — intended for static analysis tools
    return 0;
}
