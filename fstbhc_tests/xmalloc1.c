#include "aliascheck.h"

void *xmalloc(size_t s) {
    return malloc(s);
}

int main() {
    int *p = xmalloc(sizeof(int));
    int *q = xmalloc(sizeof(int));
    TBHC_MAYALIAS(p, q);
    return 0;
}
