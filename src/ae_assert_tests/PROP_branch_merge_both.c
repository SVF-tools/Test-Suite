#include <stdbool.h>

extern void svf_assert(bool);
extern void svf_assert_eq(int, int);
extern void svf_print(int, const char*);

static void update(int* x, int condition)
{
    if (condition)
        *x = 2;
    else
        *x = 3;
}

int main(int argc, char** argv)
{
    int expected = argc > 1 ? 2 : 3;
    int x = 1;
    update(&x, argc > 1);
    // Both branches overwrite 1. The precise join is [2,3], not [1,3].
    svf_print(x, "merged-x");
    svf_assert(x >= 2 && x <= 3);
    svf_assert_eq(x, expected);
    return 0;
}
