/*
 * fill_unknown has STORE_TOP but no SCANF annotation (see
 * extapi/scanf_like_extapi.c), so its outputs keep the black-hole pointer
 * under -blk. Its first argument looks like a format on purpose: it must not
 * be parsed as one.
 */
#include "aliascheck.h"

int fill_unknown(const char *tag, ...);

struct S
{
    int *p;
    int n;
};

int main(void)
{
    int x, y;
    struct S s;
    s.p = &x;
    fill_unknown("%d", (int *)((char *)&s + 8));
    int *q = s.p;
    MAYALIAS(q, &x);
    MAYALIAS(q, &y);
    return 0;
}
