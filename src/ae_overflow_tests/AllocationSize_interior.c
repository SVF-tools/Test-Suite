/* Allocation-size diagnostic regression; run with -field-limit=1024. */
// EXPECT-ALLOC-SIZE: [4, 10]

#include <stdlib.h>
#include <string.h>
extern void UNSAFE_BUFACCESS(void *buffer, int size);

int main(int argc, char **argv) {
    size_t n = argc > 1 ? 4 : 10;
    char *buffer = malloc(n);
    memset(buffer + 1, 0, 40);
    UNSAFE_BUFACCESS(buffer + 1, 39);
    free(buffer);
    return 0;
}
