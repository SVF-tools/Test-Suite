#include "aliascheck.h"

struct pair { int *first; int *second; };

/* swiftcall keeps a direct LLVM aggregate return at -O0. */
__attribute__((swiftcall, noinline))
static struct pair descend(int depth, int *p, int *q)
{
    if (depth == 0)
        return (struct pair){p, q};
    return descend(depth - 1, p, q);
}

int main(void)
{
    int x = 7, y = 9;
    /* A bounded recursive example exercises cyclic return-field discovery. */
    struct pair result = descend(2, &x, &y);
    MAYALIAS(result.first, &x);
    MAYALIAS(result.second, &y);
    NOALIAS(result.first, result.second);
    return 0;
}
