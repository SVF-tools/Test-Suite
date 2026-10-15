/* Allocation-size diagnostic regression; run with -field-limit=1024. */
// EXPECT-ALLOC-SIZE: [1, 10]

#include <stdlib.h>
#include <string.h>
extern void UNSAFE_BUFACCESS(void *buffer, int size);

int main(int argc, char **argv) {
    size_t n = argc > 1 ? 1 : 10;
    char *buffer = malloc(n);
    char source[32] = {0};
    memcpy(buffer, source, sizeof(source));
    UNSAFE_BUFACCESS(buffer, 31);
    free(buffer);
    return 0;
}
