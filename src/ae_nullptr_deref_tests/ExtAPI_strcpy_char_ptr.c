#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);  // This pointer is guaranteed safe
extern void UNSAFE_LOAD(void *ptr);  // This pointer is guaranteed unsafe

int main() {
    char* buf = (char*)malloc(20 * sizeof(char));  // Dynamically allocate memory
    char* buf_copy = (char*)malloc(20 * sizeof(char));  // Dynamically allocate memory for copy

    strcpy(buf, "Hello");  // Initialize buf with "Hello"
    strcpy(buf_copy, "World");  // Initialize buf_copy with "World"

    strcpy(buf, buf_copy);  // Copy buf_copy content to buf (valid pointer)
    strcpy(buf_copy, buf);  // Copy buf content to buf_copy (valid pointer)

    SAFE_LOAD(buf);  // Safe load: buf is valid
    SAFE_LOAD(buf_copy);  // Safe load: buf_copy is valid

    free(buf);  // Free allocated memory for buf
    UNSAFE_LOAD(buf);  // Unsafe load: buf is now invalid

    free(buf_copy);  // Free allocated memory for buf_copy
    UNSAFE_LOAD(buf_copy);  // Unsafe load: buf_copy is now invalid

    return 0;
}
