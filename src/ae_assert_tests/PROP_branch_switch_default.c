#include <stdbool.h>

extern void svf_assert(bool);
extern void svf_assert_eq(int, int);

int main(int argc, char** argv)
{
    int selector = argc > 1 ? -1 : 2;
    int expected = selector;
    switch (selector)
    {
    case 1:
        svf_assert(selector == 1);
        break;
    default:
        // Excluding 1 leaves a non-interval set. Retain its hull [-1,2].
        // The default-edge label -1 does not imply selector == -1.
        svf_assert(selector >= -1 && selector <= 2);
        svf_assert_eq(selector, expected);
        break;
    }
    return 0;
}
