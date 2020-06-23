#include <stdlib.h>
#include <stdio.h>

void f() { printf("f\n"); }
void g() { printf("g\n"); }
void (*p)();

void fake_fun (void (*a)()) {
  p = a;
  p();
}

void real_fun (void (*a)()) {
  p = a;
  p();
}

void (*fptr)(void (*p)());

void set(void (*src)()) {
  fptr = src;
}

int main(int argc, char **argv)
{
  set(&fake_fun);
  set(&real_fun);

  fptr(&f);

  fptr(&g);

  return 0;
}
