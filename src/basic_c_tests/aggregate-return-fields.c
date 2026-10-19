#include "aliascheck.h"

struct pair { int *first; int *second; };

/* swiftcall keeps pointer fields in the LLVM return aggregate at -O0,
 * so the unchanged Test-Suite generator exercises aggregate call transport. */
__attribute__((swiftcall, noinline))
static struct pair make(int *p, int *q)
{
    return (struct pair){p, q};
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
