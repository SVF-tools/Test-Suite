/*
 * read_record is annotated with SCANF:FormatArg1 (see extapi/scanf_like_extapi.c).
 * Its "%d" output must not make s.p point to the black hole under -blk,
 * although the function name does not contain "scanf".
 */
#include "aliascheck.h"

int read_record(const char *src, const char *format, ...);

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
    read_record("1", "%d", (int *)((char *)&s + 8));
    int *q = s.p;
    MAYALIAS(q, &x);
    NOALIAS(q, &y);
    return 0;
}
