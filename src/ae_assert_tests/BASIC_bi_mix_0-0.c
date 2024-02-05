#include "stdbool.h"
extern void svf_assert(bool);
int main() {
    int a, b;
    a = 1;
    a += 2 ;
    b = a;
    b -= 1;
    svf_assert( a == 3 && b == 2);


    return 0;
}