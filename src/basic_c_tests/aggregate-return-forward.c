#include "aliascheck.h"

struct pair { int *first; int *second; };

/* swiftcall keeps pointer fields in the LLVM return aggregate at -O0,
 * so the unchanged Test-Suite generator exercises aggregate call transport. */
__attribute__((swiftcall, noinline))
static struct pair make(int *p, int *q)
{
    return (struct pair){p, q};
}

__attribute__((swiftcall, noinline))
static struct pair forward(int *p, int *q)
{
    return make(p, q);
}

int main(void)
{
    int x = 7, y = 9;
    /* Unused call results must still receive the synthetic output arguments. */
    (void)make(&x, &y);
    struct pair result = forward(&x, &y);
    MAYALIAS(result.first, &x);
    MAYALIAS(result.second, &y);
    NOALIAS(result.first, result.second);
    return 0;
}
