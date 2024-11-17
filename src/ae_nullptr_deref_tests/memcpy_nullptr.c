#include <stdio.h>
#include <string.h>

int main() {
    char *src = NULL;
    char dest[20];

    memcpy(dest, src, 10);  // Attempt to copy memory from a NULL source

    printf("Destination: %s\n", dest);  // This line may cause a crash

    return 0;
}
