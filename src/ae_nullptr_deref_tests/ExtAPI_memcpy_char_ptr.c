#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern void SAFE_LOAD(void *ptr);  // This pointer is guaranteed safe
extern void UNSAFE_LOAD(void *ptr);  // This pointer is guaranteed unsafe

int main() {
    char* buf = (char*)malloc(10 * sizeof(char));  // Dynamically allocate memory
    char* buf_copy = (char*)malloc(10 * sizeof(char));  // Dynamically allocate memory for copy

    memcpy(buf, "Hello", 5);  // Copy "Hello" into buf (valid pointer)
    memcpy(buf_copy, buf, 5);  // Copy the content of buf into buf_copy

    SAFE_LOAD(buf);  // Safe load: buf is valid
    SAFE_LOAD(buf_copy);  // Safe load: buf_copy is valid

    free(buf);  // Free allocated memory for buf
    UNSAFE_LOAD(buf);  // Unsafe load: buf is now invalid

    free(buf_copy);  // Free allocated memory for buf_copy
    UNSAFE_LOAD(buf_copy);  // Unsafe load: buf_copy is now invalid

    return 0;
}
