#include <stdbool.h>
#include <string.h>

extern void svf_assert(bool);

int main(void)
{
    unsigned char a[3] = {1, 2, 3};
    memset(&a[1], 7, 1);
    // A one-byte external write updates a[1], not the complete base Obj.
    svf_assert(a[0] == 1);
    svf_assert(a[1] == 7);
    svf_assert(a[2] == 3);
    return 0;
}
