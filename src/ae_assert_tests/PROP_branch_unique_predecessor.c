#include <stdbool.h>

extern void svf_assert(bool);

static void update(int* x, int condition)
{
    if (condition)
        *x = 2;
}

int main(void)
{
    int x = 1;
    update(&x, 1);
    // The callee's merge has only its then predecessor; do not restore x=1.
    svf_assert(x == 2);
    return 0;
}
