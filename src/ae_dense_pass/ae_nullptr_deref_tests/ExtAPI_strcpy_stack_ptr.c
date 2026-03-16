#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);  // This pointer is guaranteed safe
extern void UNSAFE_LOAD(void *ptr);  // This pointer is guaranteed unsafe

int main() {
    char c;
    char* p = &c;  // Pointer to local variable
    char* p_copy = (char*)malloc(sizeof(char));  // Dynamically allocate memory for copy

    strcpy(p_copy, "A");  // Initialize p_copy with "A"
    strcpy(p_copy, "B");  // Copy "B" into p_copy

    SAFE_LOAD(p);  // Safe load: p points to a valid local variable
    SAFE_LOAD(p_copy);  // Safe load: p_copy is valid


    free(p_copy);  // Free allocated memory for p_copy
    UNSAFE_LOAD(p_copy);  // Unsafe load: p_copy is now invalid

    return 0;
}
