int g = 5;
void renamed(void) __asm__("foo.1");
void renamed(void) {}
void foo(void)
{
    int buf[4];
    buf[g] = 0;
}
int main(void) { return 0; }
