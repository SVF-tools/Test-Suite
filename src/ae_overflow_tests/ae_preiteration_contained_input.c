/* AE skips a function's component whose input is contained in the one it
 * last ran with. Both calls of wrap reach id through the same call site,
 * so id's input is wrap's n: [0, 15] at the first call, and at the second
 * the actuals of both calls joined, [0, 15] again. The second input is
 * contained in the first, so AE may skip id (full-sparse does) and keep
 * its first result. Every check below must hold after the skip. */
extern void svf_assert(int);
extern void SAFE_BUFACCESS(void *buffer, int size);

__attribute__((noinline)) static int id(int n)
{
    return n;
}

__attribute__((noinline)) static int wrap(int n)
{
    return id(n);
}

int main(int argc, char **argv)
{
    char a[16];
    int n = argc > 1 ? 15 : 0;
    int i = wrap(n);
    SAFE_BUFACCESS(a, i);
    int j = wrap(3);
    svf_assert(j >= 0 && j <= 15);
    SAFE_BUFACCESS(a, j);
    return 0;
}
