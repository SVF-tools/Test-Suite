#include <string.h>
#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);  // This pointer is guaranteed safe
extern void UNSAFE_LOAD(void *ptr);  // This pointer is guaranteed unsafe

int main() {
    int* arr = (int*)malloc(5 * sizeof(int));  // Dynamically allocate memory for 5 integers
    int* arr_copy = (int*)malloc(5 * sizeof(int));  // Dynamically allocate memory for copy

    for (int i = 0; i < 5; i++) {
        arr[i] = i;  // Initialize the array
    }

    strcat((char*)arr_copy, (char*)arr);  // Unsafe usage of strcat: casting int pointers to char pointers (not recommended, but demonstrates invalid use)
    
    SAFE_LOAD(arr);  // Safe load: arr is valid
    SAFE_LOAD(arr_copy);  // Safe load: arr_copy is valid

    free(arr);  // Free allocated memory for arr
    UNSAFE_LOAD(arr);  // Unsafe load: arr is now invalid

    free(arr_copy);  // Free allocated memory for arr_copy
    UNSAFE_LOAD(arr_copy);  // Unsafe load: arr_copy is now invalid

    return 0;
}
