extern void svf_assert_eq(int, int);
extern int nondet(void);

__attribute__((minsize)) int main(void)
{
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int i = nondet();
    int expected = nondet() ? 2 : 5;
    svf_assert_eq(a[i][1], expected);
    return 0;
}
