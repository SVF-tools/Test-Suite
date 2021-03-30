#include "aliascheck.h"

void *xmalloc(size_t s) {
    return malloc(s);
}

int main() {
    int *p = xmalloc(sizeof(int));
    float *q = xmalloc(sizeof(float));
    TBHC_NOALIAS(p, q);
    return 0;
}
