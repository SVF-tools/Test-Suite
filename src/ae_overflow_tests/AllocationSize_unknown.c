/* Allocation-size diagnostic regression; run with -field-limit=1024. */
// EXPECT-ALLOC-SIZE: [0, 1024]

#include <stdlib.h>
extern size_t unknown_size(void);
extern void UNSAFE_BUFACCESS(void *buffer, int size);

int main(int argc, char **argv) {
    char *buffer = malloc(unknown_size());
    buffer[12000] = 0;
    UNSAFE_BUFACCESS(buffer, 12000);
    free(buffer);
    return 0;
}
