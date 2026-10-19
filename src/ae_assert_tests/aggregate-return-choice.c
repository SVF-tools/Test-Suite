#include <stdbool.h>

extern void svf_assert(bool);

struct pair { int *first; int *second; };

/* swiftcall keeps pointer fields in the LLVM return aggregate at -O0,
 * so the unchanged Test-Suite generator exercises aggregate call transport. */
__attribute__((swiftcall, noinline))
static struct pair choose(int condition, int *p, int *q)
{
    if (condition != 0)
        return (struct pair){p, q};
    return (struct pair){q, p};
}

int main(void)
{
    int x = 7, y = 9;
    struct pair result = choose(1, &x, &y);
    svf_assert(*result.first == 7);
    svf_assert(*result.second == 9);
    return 0;
}
