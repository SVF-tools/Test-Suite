#include <stdbool.h>

extern void set_value(int, int, int);
extern void svf_assert(bool);

int main(void)
{
    int x = 3;
    set_value(x, 0, 10);
    if (x >= 2 && x < 5)
    {
        // Both uses must inherit x in [2,4], not the original [0,10].
        svf_assert(x >= 2 && x <= 4);
        int y = x + 1;
        svf_assert(y >= 3 && y <= 5);
    }
    return 0;
}
