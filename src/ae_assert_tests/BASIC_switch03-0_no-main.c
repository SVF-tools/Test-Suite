#include "stdbool.h"
extern void svf_assert(bool);

int nd(void)
{
    return 1;
}

int no_main_BASIC_switch03_0() {
    int x, y;
    x = 1;
    y = 0;
    switch (nd())
    {
        case 1:
            x += 1;
            break;
        case 0:
            x += y;
            break;
        case 2:
            x -= y;
            break;
        default:
            x++;
            y++;
            break;
    }
    svf_assert(x >= y);
    return 0;
}