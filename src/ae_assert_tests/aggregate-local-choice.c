#include <stdbool.h>

extern void svf_assert(bool);

struct pair { int *first; int *second; };

/* swiftcall returns pointer fields in an LLVM aggregate at -O0. Inlining
 * leaves insertvalue/extractvalue in the caller for local-field coverage. */
__attribute__((swiftcall, always_inline))
static inline struct pair choose(int condition, int *p, int *q)
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
