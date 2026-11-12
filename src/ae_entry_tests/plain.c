void foo(int n)
{
    int buf[4];
    if (n == 5)
        buf[n] = 0;
}
/* The actual argument must not constrain a custom analysis entry. */
int main(void) { foo(0); return 0; }
