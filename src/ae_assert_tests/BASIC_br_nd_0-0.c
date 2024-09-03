
// CHECK: ^sat$

extern int nd(void);

#include "stdbool.h"

extern void svf_assert(bool);
extern void svf_assert_eq(int, int);

int main() {
    int x, y;
    x = 1;
    y = 1;

    if (nd()) {
        x++;
        y++;
    }
    svf_assert(x <=10);
    svf_assert_eq(x, y);
    return 0;
}
