#include "aliascheck.h"

struct pair { int *first; int *second; };

/* swiftcall returns pointer fields in an LLVM aggregate at -O0. Inlining
 * leaves insertvalue/extractvalue in the caller for local-field coverage. */
__attribute__((swiftcall, always_inline))
static inline struct pair make(int *p, int *q)
{
    struct pair result = {p, q};
    return result;
}

int main(void)
{
    int x = 7, y = 9;
    struct pair result = make(&x, &y);
    MAYALIAS(result.first, &x);
    MAYALIAS(result.second, &y);
    NOALIAS(result.first, result.second);
    return 0;
}
