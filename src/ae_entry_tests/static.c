#line 1 "/x/src/a.c"
static void foo(void) {}
#line 1 "/x/src/b.c"
static void foo_b(void) __asm__("foo.1");
static void foo_b(void)
{
    int buf[4];
    buf[5] = 0;
}
int main(void) { foo(); foo_b(); return 0; }
