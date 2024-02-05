// CHECK: ^unsat$
#include "stdbool.h"
extern void svf_assert(bool);
extern int nd_int(void);
void c (int*);

int main(int argc, char** argv) {
  void (*q) (int*) = c;
  nd_int();

  int y = 5;
  q(&y); // the indirect call returns an integer

  svf_assert(y >= 7);
}

void c(int* x) {
  *x = *x+5;
  nd_int();
}
