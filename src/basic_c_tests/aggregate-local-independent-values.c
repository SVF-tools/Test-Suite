#include "aliascheck.h"

struct pair { int *first; int *second; };

/* swiftcall plus inlining retains local pointer insertvalue/extractvalue
 * instructions in the unchanged -O0 generation pipeline. */
__attribute__((swiftcall, always_inline))
static inline struct pair make(int *p, int *q)
{
    return (struct pair){p, q};
}

int main(void)
{
    int a = 1, b = 2, c = 3, d = 4;
    struct pair first = make(&a, &b);
    struct pair second = make(&c, &d);
    /* Two inlined aggregate values must not share the same field identity. */
    MAYALIAS(first.first, &a);
    MAYALIAS(second.first, &c);
    NOALIAS(first.first, second.first);
    NOALIAS(first.second, second.second);
    return 0;
}
