
// CHECK: ^sat$


#include "stdbool.h"

extern void svf_assert(bool);

int main() {
    int x;
    x = 1;

    if (false) {
        x++;
    }
    svf_assert(x != 2);
    return 0;
}