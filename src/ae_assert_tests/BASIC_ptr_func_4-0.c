// CHECK: ^unsat$
#include "stdbool.h"
extern void svf_assert(bool);
extern int nd_int(void);
int c (int*);

int main(int argc, char** argv) {
  int (*q) (int*);
  if (nd_int()) {
    q = c;
  } else {
      q = c;
  }
  int y = 5;
  int r = q(&y); // the indirect call returns an integer

  svf_assert(y >= 7);
}

int c(int* x) {
  *x = *x+5;
  return (nd_int() ? 0: 1);
}
