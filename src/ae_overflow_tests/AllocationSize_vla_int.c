/* Allocation-size diagnostic regression; run with -field-limit=1024. */
// EXPECT-ALLOC-SIZE: [4, 40]
// KNOWN-ALLOC-SIZE: [1, 10]
/* Known issue: dynamic alloca sizes omit sizeof(int), unlike constant allocas. */

#include <stddef.h>
extern void UNSAFE_BUFACCESS(void *buffer, int size);

int main(int argc, char **argv) {
    size_t n = argc > 1 ? 1 : 10;
    int buffer[n];
    buffer[12000] = 0;
    UNSAFE_BUFACCESS(buffer, 12000 * sizeof(int));
    return 0;
}
