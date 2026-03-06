#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);
extern void UNSAFE_LOAD(void *ptr);

void test_safe_strcat() {
    char *a = (char *)malloc(20);
    char *b = (char *)malloc(20);
    if (a && b) {
        strcpy(a, "Hello");
        strcpy(b, " World");

        // Safe usage
        SAFE_LOAD(a);  // Access before strcat
        SAFE_LOAD(b);

        strcat(a, b);  // Concatenate strings
    }
    free(a);
    free(b);
}

void test_unsafe_strcat() {
    char *a = NULL;
    char *b = (char *)malloc(20);
    if (b) {
        strcpy(b, " World");

        // Unsafe usage
        UNSAFE_LOAD(a);  // a is NULL — this is unsafe
        SAFE_LOAD(b);  // b is valid

        strcat(a, b);  // Undefined behavior (null dereference)
    }
    free(b);
}

int main() {
    test_safe_strcat();
    test_unsafe_strcat();  // This will likely crash — intended for static analysis tools like SVF
    return 0;
}
