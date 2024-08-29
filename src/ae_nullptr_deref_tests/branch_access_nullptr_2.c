#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int));  // Allocate memory

    int a = 0;

    if (a < 0) {
        ptr = NULL; // this is not feasible but is still a potential null pointer dereference
    }

    int b = *ptr;

    return 0;
}
