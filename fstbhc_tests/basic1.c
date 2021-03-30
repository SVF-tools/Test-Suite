#include "aliascheck.h"

int main() {
    int *p = malloc(sizeof(int));
    int *q = malloc(sizeof(int));
    TBHC_NOALIAS(p, q);
    return 0;
}
