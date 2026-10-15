/* Allocation-size diagnostic regression; run with -field-limit=1024. */
// EXPECT-ALLOC-SIZE: [10, 10]

extern void UNSAFE_BUFACCESS(void *buffer, int size);

int main(int argc, char **argv) {
    char buffer[10];
    buffer[12000] = 0;
    UNSAFE_BUFACCESS(buffer, 12000);
    return 0;
}
