#include <stdbool.h>

extern void set_value(int, int, int);
extern void svf_assert(bool);

int main(void)
{
    int x = 3;
    set_value(x, 0, 10);
    if (x < 5)
    {
        x = 10;
        // The constraint on the old x must not constrain the new store.
        svf_assert(x == 10);
    }
    return 0;
}
