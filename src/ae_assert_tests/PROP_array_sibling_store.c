#include <stdbool.h>

extern void svf_assert(bool);

int main(void)
{
    int a[3] = {1, 2, 3};
    a[1] = 10;
    // Propagate the base and existing sub-Objs, but update only a[1].
    svf_assert(a[0] == 1);
    svf_assert(a[1] == 10);
    svf_assert(a[2] == 3);
    return 0;
}
