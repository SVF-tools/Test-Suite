void b(int n);
void a(int n) { if (n > 0) b(n - 1); }
void b(int n)
{
    int buf[4];
    if (n == 5) buf[n] = 0;
    a(n);
}
int main(void) { a(1); return 0; }
