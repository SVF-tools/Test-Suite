#include <stdio.h>
#include <string.h>
extern void UNSAFE_BUFACCESS(void *buffer, int size);

int main() {
    char buffer[10] = "Hi";
    char input[20];
    printf("Enter a string: ");
    scanf("%19s", input);
    strcat(buffer, input);
    UNSAFE_BUFACCESS(buffer, strlen(buffer));
    printf("Buffer: %s\n", buffer);
    return 0;
}
