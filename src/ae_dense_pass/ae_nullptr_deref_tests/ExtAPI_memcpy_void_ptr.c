#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);  // This pointer is guaranteed safe
extern void UNSAFE_LOAD(void *ptr);  // This pointer is guaranteed unsafe

int main() {
    void* p = malloc(20);  // Dynamically allocate 20 bytes of memory
    void* p_copy = malloc(20);  // Dynamically allocate memory for copy

    memcpy(p, "Hello", 5);  // Copy "Hello" into p
    memcpy(p_copy, p, 5);   // Copy the content of p into p_copy

    SAFE_LOAD(p);  // Safe load: p is valid
    SAFE_LOAD(p_copy);  // Safe load: p_copy is valid

    free(p);  // Free allocated memory for p
    UNSAFE_LOAD(p);  // Unsafe load: p is now invalid

    free(p_copy);  // Free allocated memory for p_copy
    UNSAFE_LOAD(p_copy);  // Unsafe load: p_copy is now invalid

    return 0;
}
