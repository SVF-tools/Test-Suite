#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>

int main () {
   int a;
   int b = a;
   loopStart: do {
      if(a == b) {
         a++;
         goto loopStart;
      }
      a++;
      b++;
   } while(a < 15);
   svf_assert(b == a - 1 && a >= 15);
}
