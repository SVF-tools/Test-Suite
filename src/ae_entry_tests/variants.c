void first(void) __asm__("foo.1");
void second(void) __asm__("foo.2");
void first(void) {}
void second(void) {}
int main(void) { return 0; }
