/* Allocation-size diagnostic regression; run with -field-limit=1024. */
// EXPECT-ALLOC-SIZE: [3, 30]

#include <stdlib.h>
extern void UNSAFE_BUFACCESS(void *buffer, int size);

int main(int argc, char **argv) {
    size_t n = argc > 1 ? 1 : 10;
    char *buffer = calloc(n, 3);
    buffer[12000] = 0;
    UNSAFE_BUFACCESS(buffer, 12000);
    free(buffer);
    return 0;
}
