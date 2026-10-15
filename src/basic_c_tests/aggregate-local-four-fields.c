#include "aliascheck.h"

struct four { int *a; int *b; int *c; int *d; };

/* swiftcall plus inlining retains local pointer insertvalue/extractvalue
 * instructions in the unchanged -O0 generation pipeline. */
__attribute__((swiftcall, always_inline))
static inline struct four make(int *a, int *b, int *c, int *d)
{
    return (struct four){a, b, c, d};
}

int main(void)
{
    int a = 1, b = 2, c = 3, d = 4;
    struct four value = make(&a, &b, &c, &d);
    /* Check every field, in reverse order, against its distinct object. */
    MAYALIAS(value.d, &d);
    MAYALIAS(value.c, &c);
    MAYALIAS(value.b, &b);
    MAYALIAS(value.a, &a);
    NOALIAS(value.a, value.d);
    NOALIAS(value.b, value.c);
    return 0;
}
