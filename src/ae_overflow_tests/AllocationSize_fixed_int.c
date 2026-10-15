/* Allocation-size diagnostic regression; run with -field-limit=1024. */
// EXPECT-ALLOC-SIZE: [40, 40]

extern void UNSAFE_BUFACCESS(void *buffer, int size);

int main(int argc, char **argv) {
    int buffer[10];
    buffer[12000] = 0;
    UNSAFE_BUFACCESS(buffer, 12000 * sizeof(int));
    return 0;
}
