#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);  // This pointer is guaranteed safe
extern void UNSAFE_LOAD(void *ptr);  // This pointer is guaranteed unsafe

int main() {
    int* arr = (int*)malloc(5 * sizeof(int));  // Dynamically allocate memory for 5 integers
    memset(arr, 0, 5 * sizeof(int));  // Set all 5 integers to 0 (valid pointer)

    SAFE_LOAD(arr);  // Safe load: arr is guaranteed to be valid

    free(arr);  // Free allocated memory

    UNSAFE_LOAD(arr);  // Unsafe load: arr is now invalid, as it points to freed memory

    return 0;
}
