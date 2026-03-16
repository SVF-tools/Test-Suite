#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);  // This pointer is guaranteed safe
extern void UNSAFE_LOAD(void *ptr);  // This pointer is guaranteed unsafe

int main() {
    char c;
    char* p = &c;  // Pointer to local variable
    memset(p, 0, 1);  // Set the value of the local variable 'c' to 0 (valid pointer)

    SAFE_LOAD(p);  // Safe load: p points to a valid local variable, safe

    // We don't need to free 'p' as it's pointing to a local variable
    // UNSAFE_LOAD(p);  // This would be invalid, 'p' is valid and local

    return 0;
}
