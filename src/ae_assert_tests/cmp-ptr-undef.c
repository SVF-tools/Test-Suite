/* Pointer counterpart of cmp-int-undef.c.
 * After mem2reg, the uninitialized pointer becomes `icmp ne ptr undef, @object`.
 * An unknown pointer may or may not equal &object, so the result must be
 * exactly [0, 1]. */
extern void svf_assert_eq(int, int);

int object;

/* minsize keeps clang -O0 from adding optnone, so mem2reg promotes p to undef. */
__attribute__((minsize)) static int compare_uninit(void)
{
    int *p;
    return (p != &object) ? 1 : 0;
}

int main(int argc, char **argv)
{
    int r = compare_uninit();
    /* argc is unknown, so expected is the interval [0, 1]. */
    int expected = (argc == 1) ? 1 : 0;
    svf_assert_eq(r, expected);
    return 0;
}
