
#include "stdbool.h"
extern void svf_assert(bool);
int main() {
  int a = 1;
  int b = 2;
  int c = a * b;
  svf_assert(c == 2);
  return 0;
}