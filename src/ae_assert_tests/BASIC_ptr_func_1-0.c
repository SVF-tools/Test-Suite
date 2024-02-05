// CHECK: ^unsat$
#include "stdbool.h"
extern void svf_assert(bool);
extern int nd_int(void);

int a (void);
int c (int);

int main() {
  int (*p) (void);
  int (*q) (int);  
  
  if (nd_int()) {
      p = a;
      q = c;
  }

  int x = p();
  int y = q(2);

  svf_assert(x>= 5 && y>= 7);    

  return 0;
}

int a() {return 10;}
int c(int x) {return x+5;}
