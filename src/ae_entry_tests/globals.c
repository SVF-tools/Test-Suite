int g = 5;
void foo(void)
{
    int buf[4];
    buf[g] = 0;
}
int main(void) { return 0; }
