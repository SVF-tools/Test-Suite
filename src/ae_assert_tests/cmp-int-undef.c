/* Reproducer for an icmp over an integer undef operand.
 * After mem2reg, the uninitialized local becomes `icmp ne i32 undef, 0`. */
#include <stdbool.h>

extern void svf_assert(bool);

/* minsize keeps clang -O0 from adding optnone, so mem2reg promotes x to undef. */
__attribute__((minsize)) static int compare_uninit(void)
{
    int x;
    return (x != 0) ? 1 : 0;
}

int main(void)
{
    int r = compare_uninit();
    svf_assert(r >= 0 && r <= 1);
    return 0;
}
