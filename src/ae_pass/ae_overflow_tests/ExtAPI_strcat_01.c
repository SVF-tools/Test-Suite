#include <stdio.h>
#include <string.h>
extern void UNSAFE_BUFACCESS(void *buffer, int size);

int main() {
    char buffer[10];
    char *largeString = "worldworld";
    strcpy(buffer, "Hello");
    strcat(buffer, largeString);
    UNSAFE_BUFACCESS(buffer, 5 + 10 + 1); // Hello 5, worldworld 10, null terminator 1
    return 0;
}
