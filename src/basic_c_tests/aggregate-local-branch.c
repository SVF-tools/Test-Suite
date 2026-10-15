#include "aliascheck.h"

struct pair { int *first; int *second; };

/* swiftcall returns pointer fields in an LLVM aggregate at -O0. Inlining
 * leaves insertvalue/extractvalue in the caller for local-field coverage. */
__attribute__((swiftcall, always_inline))
static inline struct pair choose(int condition, int *p, int *q)
{
    if (condition)
        return (struct pair){p, q};
    return (struct pair){q, p};
}

int main(int argc, char **argv)
{
    int x = 7, y = 9, z = 11;
    struct pair result = choose(argc > 1, &x, &y);
    MAYALIAS(result.first, &x);
    MAYALIAS(result.first, &y);
    NOALIAS(result.first, &z);
    return 0;
}
