/* Allocation-size diagnostic regression; run with -field-limit=1024. */
// EXPECT-NO-OVERFLOW

#include <stddef.h>
extern void SAFE_BUFACCESS(void *buffer, int size);

int main(int argc, char **argv) {
    size_t n = argc > 1 ? 1 : 10;
    char buffer[n];
    buffer[0] = 0;
    SAFE_BUFACCESS(buffer, 0);
    return 0;
}
