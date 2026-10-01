/*
 * The format is not a constant string, so it may contain "%p".
 * The output keeps the black-hole pointer under -blk.
 */
#include "aliascheck.h"

struct S
{
    int *p;
    int n;
};

int main(int argc, char **argv)
{
    int x, y;
    struct S *s = malloc(sizeof(struct S));
    s->p = &x;
    sscanf("1", argv[0], (int *)((char *)s + 8));
    int *q = s->p;
    MAYALIAS(q, &x);
    MAYALIAS(q, &y);
    return 0;
}
