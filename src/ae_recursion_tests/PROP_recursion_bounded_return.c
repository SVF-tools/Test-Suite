#include <stdbool.h>

extern void svf_assert(bool);

static int bounded_id(int n)
{
    if (n <= 0)
        return 0;
    int result = bounded_id(n - 1) + 1;
    if (result > 2)
        return 2;
    return result;
}

int main(void)
{
    int result = bounded_id(3);
    // Recursive return states should retain the function's [0,2] bound.
    svf_assert(result >= 0 && result <= 2);
    return 0;
}
