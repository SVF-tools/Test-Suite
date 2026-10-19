#include "aliascheck.h"

struct pair { int *first; int *second; };

/* swiftcall keeps a direct LLVM aggregate return at -O0. */
__attribute__((swiftcall, noinline))
static struct pair make(int *p, int *q)
{
    return (struct pair){p, q};
}

__attribute__((swiftcall, noinline))
static struct pair left(int *p, int *q)
{
    return make(p, q);
}

__attribute__((swiftcall, noinline))
static struct pair right(int *p, int *q)
{
    return make(p, q);
}

int main(void)
{
    int a = 1, b = 2, c = 3, d = 4;
    struct pair first = left(&a, &b);
    struct pair second = right(&c, &d);
    /* Context-insensitive analyses may merge callers, but not field positions. */
    MAYALIAS(first.first, &a);
    MAYALIAS(second.first, &c);
    MAYALIAS(first.second, &b);
    MAYALIAS(second.second, &d);
    NOALIAS(first.first, second.second);
    return 0;
}
