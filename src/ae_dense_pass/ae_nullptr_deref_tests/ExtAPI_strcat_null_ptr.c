#include <string.h>
#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);  // This pointer is guaranteed unsafe

int main() {
    char* p = NULL;  // NULL pointer
    char* p_copy = malloc(20 * sizeof(char));  // Dynamically allocate memory for copy

    strcpy(p_copy, "Hello");  // Initialize p_copy with "Hello"
    strcat(p, p_copy);  // Unsafe operation: p is NULL, this is invalid

    free(p_copy);  // Free allocated memory for p_copy
    UNSAFE_LOAD(p_copy);  // Unsafe load: p_copy is now invalid

    free(p);  // Freeing a NULL pointer is safe, but p is still unsafe
    UNSAFE_LOAD(p);  // Unsafe load: p is still NULL after free

    return 0;
}
