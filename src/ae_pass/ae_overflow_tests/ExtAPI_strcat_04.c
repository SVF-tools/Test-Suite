#include <stdio.h>
#include <string.h>
extern void UNSAFE_BUFACCESS(void *buffer, int size);
int main() {
    char buffer[15] = "Start";
    char *string1 = "12345";
    char *string2 = "67890";
    strcat(buffer, string1);
    strcat(buffer, string2);
    UNSAFE_BUFACCESS(buffer, 5 + strlen(string1) + strlen(string2));
    printf("Buffer: %s\n", buffer);
    return 0;
}
