#include "stdbool.h"
extern void svf_assert(bool);
extern void set_value(int, int, int);
#include <assert.h>

void foo(int* i) {
    int a = *i % 2;
    switch (a) 
    {
        case 0:
            break;
        case 1:
            *i = *i + 1;
            break;
        default:
            *i = *i + 3;
            break;
    }
}

int main() {
    int i;
    set_value(i, 1, 1);
    if (i >= 0) {
        foo(&i);
        svf_assert(i % 2 == 0);
    }
}