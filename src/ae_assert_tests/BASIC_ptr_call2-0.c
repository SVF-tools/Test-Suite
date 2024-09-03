// CHECK: ^unsat$
#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_assert_eq(int, int);
extern void svf_print(int, char*);
extern void set_value(int, int, int);

int a (void);
int c (int);

int main() {
  int y = c(2);
  int x = c(3);
  int res;
  set_value(res, 2, 3);
  svf_print(x, "X");
  svf_assert_eq(x, res);

  return 0;
}

int c(int z) {return z;}
