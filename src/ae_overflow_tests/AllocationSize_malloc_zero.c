/* Allocation-size diagnostic regression; run with -field-limit=1024. */
// EXPECT-ALLOC-SIZE: [0, 10]

#include <stdlib.h>
extern void UNSAFE_BUFACCESS(void *buffer, int size);

int main(int argc, char **argv) {
    size_t n = argc > 1 ? 0 : 10;
    char *buffer = malloc(n);
    buffer[12000] = 0;
    UNSAFE_BUFACCESS(buffer, 12000);
    free(buffer);
    return 0;
}
