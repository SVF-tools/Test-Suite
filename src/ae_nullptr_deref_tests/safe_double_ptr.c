#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);

int main() {
    int **dp = malloc(sizeof(int *));
    *dp = malloc(sizeof(int));
    **dp = 1;
    SAFE_LOAD(dp);
    SAFE_LOAD(*dp);
}
