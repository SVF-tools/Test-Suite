#include "aliascheck.h"

struct result { int *first; long tag; int *last; };

/* swiftcall keeps a direct LLVM aggregate return at -O0. */
__attribute__((swiftcall, noinline))
static struct result make(int *p, int *q)
{
    return (struct result){p, 23, q};
}

int main(void)
{
    int x = 7, y = 9;
    struct result value = make(&x, &y);
    /* Pointer fields are separated by a scalar; consume the last field first. */
    MAYALIAS(value.last, &y);
    MAYALIAS(value.first, &x);
    NOALIAS(value.first, value.last);
    return 0;
}
