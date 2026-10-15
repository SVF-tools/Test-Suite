#include <stdbool.h>

extern void svf_assert(bool);

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
    int x = 7, y = 9, z = 11;
    struct pair first = make(&x, &y);
    struct pair second = make(&z, &y);
    /* The first result must survive completion of the second call. */
    svf_assert(*first.first == 7);
    svf_assert(*first.second == 9);
    return 0;
}
