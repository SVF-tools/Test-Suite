void foo(void) __asm__("only.7");
void foo(void)
{
    int buf[4];
    buf[5] = 0;
}
void nonnumeric(void) __asm__("literal.end");
void nonnumeric(void) { foo(); }
void nested(void) __asm__("nested.1.2");
void nested(void) { foo(); }
int main(void) { return 0; }
