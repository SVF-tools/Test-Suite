/*
 * sscanf with "%p" can write an address, so the output keeps the black-hole
 * pointer under -blk and q may alias any object.
 */
#include "aliascheck.h"

struct S
{
    int *p;
    int n;
};

int main(void)
{
    int x, y;
    struct S *s = malloc(sizeof(struct S));
    s->p = &x;
    sscanf("0x1", "%p", (void **)((char *)s + 8));
    int *q = s->p;
    MAYALIAS(q, &x);
    MAYALIAS(q, &y);
    return 0;
}
