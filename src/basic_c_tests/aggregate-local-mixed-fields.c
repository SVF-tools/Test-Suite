#include "aliascheck.h"

struct result { int *first; long tag; int *last; };

/* swiftcall plus inlining retains local pointer insertvalue/extractvalue
 * instructions in the unchanged -O0 generation pipeline. */
__attribute__((swiftcall, always_inline))
static inline struct result make(int *p, int *q)
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
