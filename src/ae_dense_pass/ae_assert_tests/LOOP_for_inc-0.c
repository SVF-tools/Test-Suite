#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_assert_eq(int, int);
extern void set_value(int, int, int);
extern void svf_print(int, char*);
int main() {
    int i = 0;
    for (i = 0; i < 5; i++) {
        i++;
    }
    int res;
    set_value(res, 5, 6);
    svf_assert_eq(i, res);
}
