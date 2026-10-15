#include <stdbool.h>

extern void svf_assert(bool);
extern void svf_assert_eq(int, int);
extern void svf_print(int, const char*);

int main(int argc, char** argv)
{
    int expected_x = argc > 1 ? 1 : 2;
    int expected_y = argc > 1 ? 2 : 3;
    int x = 1, y = 3;
    int* pointer = argc > 1 ? &x : &y;
    *pointer = 2;
    // Only one concrete target changes. Both abstract targets need weak updates.
    svf_print(x, "weak-x");
    svf_print(y, "weak-y");
    svf_assert(x >= 1 && x <= 2 && y >= 2 && y <= 3);
    svf_assert_eq(x, expected_x);
    svf_assert_eq(y, expected_y);
    return 0;
}
