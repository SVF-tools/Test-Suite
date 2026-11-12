extern void svf_assert(int);
int g = 5;
void foo(void)
{
    svf_assert(g == 5);
    g = 2;
    svf_assert(g == 2);
}
int main(void) { return 0; }
