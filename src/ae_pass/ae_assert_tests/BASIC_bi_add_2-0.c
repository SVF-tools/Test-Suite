#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_assert_eq(int, int);
extern void set_value(int, int, int);
extern void svf_print(int, char*);
int main() {
    volatile int i;
    set_value(i, 0, 100);
    volatile int a, c;
    a = i + 1;
    c = a;
    svf_assert_eq(c, i+1);
    return 0;
}