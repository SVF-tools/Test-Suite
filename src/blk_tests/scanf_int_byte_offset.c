/*
 * sscanf with "%d" writes a number, not an address.
 * Under -blk, the output must not make s->p point to the black hole.
 *
 * The output is addressed by a byte offset, as in optimized code. SVF does not
 * resolve (char *)s + 8 to field n, so a pointer store through it would reach
 * the field that holds p.
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
    sscanf("1", "%d", (int *)((char *)s + 8));
    int *q = s->p;
    MAYALIAS(q, &x);
    NOALIAS(q, &y);
    return 0;
}
