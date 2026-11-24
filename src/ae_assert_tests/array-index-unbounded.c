extern void svf_assert_eq(int, int);
extern int nondet(void);

__attribute__((minsize)) int main(void)
{
    int a[4] = {1, 2, 3, 4};
    int i = nondet();
    int expected = nondet() ? 1 : 4;
    svf_assert_eq(a[i], expected);
    return 0;
}
