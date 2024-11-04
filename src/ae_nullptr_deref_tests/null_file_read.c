#include <stdio.h>

int main() {
    FILE *file = NULL;

    // Attempting to read from a NULL file pointer
    char buffer[100];
    size_t read_count = fread(buffer, sizeof(char), 100, file);  // Triggers a null pointer dereference
    printf("Bytes read: %zu\n", read_count);

    return 0;
}