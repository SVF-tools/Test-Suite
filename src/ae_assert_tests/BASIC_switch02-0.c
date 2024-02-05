#include "stdbool.h"
#include <stdio.h>
extern void svf_assert(bool);


int main() {
    int x, y;
    x = 1;
    y = 0;
    char cond = 'a';
    switch (cond)
    {
        case 'a':
            x += 1;
            break;
        case 'bb':
            x += y;
        case 'c':
            x -= y;
        default:
            x++;
            y++;
            break;
    }
    svf_assert(x >= y);
    return 0;
}