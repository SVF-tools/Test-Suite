#include <stdbool.h>

extern void svf_assert(bool);

struct pair { int *first; int *second; };

/* swiftcall plus inlining retains local pointer insertvalue/extractvalue
 * instructions in the unchanged -O0 generation pipeline. */
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
    struct pair result = choose(0, &x, &y);
    svf_assert(*result.first == 9);
    svf_assert(*result.second == 7);
    return 0;
}
