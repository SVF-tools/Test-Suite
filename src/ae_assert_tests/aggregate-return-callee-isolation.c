#include <stdbool.h>

extern void svf_assert(bool);

struct pair { int *first; int *second; };

/* swiftcall keeps a direct LLVM aggregate return at -O0. */
__attribute__((swiftcall, noinline))
static struct pair left(int *p, int *q)
{
    return (struct pair){p, q};
}

__attribute__((swiftcall, noinline))
static struct pair right(int *p, int *q)
{
    return (struct pair){q, p};
}

int main(void)
{
    int a = 1, b = 2, c = 3, d = 4;
    struct pair first = left(&a, &b);
    struct pair second = right(&c, &d);
    /* Same LLVM result type, different callees and output-field mappings. */
    svf_assert(*first.first == 1);
    svf_assert(*first.second == 2);
    svf_assert(*second.first == 4);
    svf_assert(*second.second == 3);
    return 0;
}
