#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);  // This pointer is guaranteed safe
extern void UNSAFE_LOAD(void *ptr);  // This pointer is guaranteed unsafe

int main() {
    char* buf = (char*)malloc(10 * sizeof(char));  // Dynamically allocate memory
    memset(buf, 0, 10);  // Set all 10 bytes to 0 (valid pointer)

    SAFE_LOAD(buf);  // Safe load: buf is guaranteed to be valid

    free(buf);  // Free allocated memory

    UNSAFE_LOAD(buf);  // Unsafe load: buf is now invalid, as it points to freed memory

    return 0;
}
