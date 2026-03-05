#include "stdbool.h"
extern void svf_assert(bool);

int nd(void)
{
    return 1;
}

int main() {
    int x, y;
    x = 1;
    y = 0;
    const int i = 1;
    switch (x)
    {
        case 0:
            x += 1;
            break;
        case i:
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