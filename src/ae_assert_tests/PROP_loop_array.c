#include <stdbool.h>

extern void svf_assert(bool);
extern void svf_print(int, const char*);

int main(void)
{
    int a[2] = {7, 0};
    int i = 0;
    while (i < 3)
    {
        a[1] = i;
        i = i + 1;
    }
    // Loop stores participate in the fixpoint; the sibling a[0] stays 7.
    // [0,2] is sufficient here; demanding the exact last value is separate.
    svf_print(a[1], "loop-array-value");
    svf_assert(a[1] >= 0 && a[1] <= 2);
    svf_assert(a[0] == 7);
    return 0;
}
