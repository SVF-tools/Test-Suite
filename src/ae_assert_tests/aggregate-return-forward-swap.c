#include <stdbool.h>

extern void svf_assert(bool);

struct pair { int *first; int *second; };

/* swiftcall keeps a direct LLVM aggregate return at -O0. */
__attribute__((swiftcall, noinline))
static struct pair make(int *p, int *q)
{
    return (struct pair){p, q};
}

__attribute__((swiftcall, noinline))
static struct pair swap(int *p, int *q)
{
    struct pair inner = make(p, q);
    /* Consume one return interface and produce another with reversed fields. */
    return (struct pair){inner.second, inner.first};
}

int main(void)
{
    int x = 7, y = 9;
    struct pair result = swap(&x, &y);
    svf_assert(*result.first == 9);
    svf_assert(*result.second == 7);
    return 0;
}
