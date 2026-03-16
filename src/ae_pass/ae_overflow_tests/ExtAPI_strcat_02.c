#include <stdio.h>
#include <string.h>
extern void UNSAFE_BUFACCESS(void *buffer, int size);
int main() {
    char buffer[20] = "";
    char *strings[] = {"Hello", "World", "This", "Is", "Too", "Long"};
    int i;
    for (i = 0; i < 6; i++) {
        strcat(buffer, strings[i]);
    }
    UNSAFE_BUFACCESS(buffer, 23);
    printf("Buffer: %s\n", buffer);

    return 0;
}
