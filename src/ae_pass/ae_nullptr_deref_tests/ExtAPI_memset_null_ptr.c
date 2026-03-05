#include <string.h>
#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);  // This pointer is guaranteed unsafe

int main() {
    char* p = NULL;  // NULL pointer
    UNSAFE_LOAD(p);  // Unsafe load: p is guaranteed to be NULL, unsafe

    free(p);  // Freeing a NULL pointer is safe, but p is still unsafe
    UNSAFE_LOAD(p);  // Unsafe load: p is still NULL after free

    return 0;
}
