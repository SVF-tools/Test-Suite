
#include "stdbool.h"
extern void svf_assert(bool);
int no_main_BASIC_bi_mul_0_0() {
  int a = 1;
  int b = 2;
  int c = a * b;
  svf_assert(c == 2);
  return 0;
}