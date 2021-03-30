#include "aliascheck.h"

void *xmalloc(size_t s) {
    return malloc(s);
}

int main() {
    int *p = xmalloc(sizeof(int));
    float *q = xmalloc(sizeof(float));
    int *r = xmalloc(sizeof(int));

    TBHC_NOALIAS(p, q);
    TBHC_MAYALIAS(p, r);
    TBHC_NOALIAS(q, r);

    return 0;
}
