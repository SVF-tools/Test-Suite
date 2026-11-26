#include <stdbool.h>

extern void svf_assert(bool);
extern void svf_assert_eq(int, int);

/* Reachable from the entry: svf_assert is a checkpoint, so AE aborts if it is never visited. */
void callee(void)
{
    int x = 1;
    svf_assert(x == 1);
}

void entry(void)
{
    callee();
}

/* Not reachable from the entry: svf_assert_eq is not a checkpoint, and this one fails if visited. */
int main(void)
{
    svf_assert_eq(0, 1);
    entry();
    return 0;
}
