//
// Created by 12425 on 2025/5/1.
//

#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);  // This pointer is guaranteed safe
extern void UNSAFE_LOAD(void *ptr);  // This pointer is guaranteed unsafe

int main() {
    void* p = malloc(20);  // Dynamically allocate 20 bytes of memory
    memset(p, 0, 20);      // Set all 20 bytes to 0 (valid pointer)

    SAFE_LOAD(p);  // Safe load: p is guaranteed to be valid

    free(p);               // Free allocated memory

    UNSAFE_LOAD(p);  // Unsafe load: p is now invalid, as it points to freed memory

    return 0;
}

