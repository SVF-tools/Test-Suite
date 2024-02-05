// CHECK: ^unsat$
#include "stdbool.h"
extern void svf_assert(bool);

int a (void);
int c (int);

int main() {

  int y = c(2);
  int x = c(3);

  svf_assert(x== 3);    

  return 0;
}

int c(int z) {return z;}
