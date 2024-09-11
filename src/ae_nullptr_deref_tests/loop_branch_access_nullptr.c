#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p;
    int i = 0;
    while (i < 100) {
        if (i == 50) {
            p = NULL;
        }
        else {
            p = malloc(sizeof(int));
        }
        *p = 42;
        i++;
    }

    return 0;
}
