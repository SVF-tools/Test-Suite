#include <stdbool.h>

extern void svf_assert(bool);

int main(void)
{
    int x;
    /* Materialize the result without a zext, which loses interval precision in AE. */
    int r = (x != 0) ? 1 : 0;
    svf_assert(r >= 0 && r <= 1);
    return 0;
}
