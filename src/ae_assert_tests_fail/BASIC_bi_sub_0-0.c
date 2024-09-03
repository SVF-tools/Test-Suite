#include "stdbool.h"
extern void svf_assert(bool);
extern void set_value(int, int, int);
extern void svf_assert_eq(int, int);
int main() {
    int i;
    set_value(i, 0, 100);
    int a, c;
    a = i - 1;
    c = a;
    svf_assert_eq(c, i - 1);
    return 0;
}