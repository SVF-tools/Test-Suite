#include "stdbool.h"
extern void svf_assert(bool);
int main() {
    int a, b;
    a = 1;
    a += 2 ;
    b = a;
    svf_assert( b == 3 );
    return 0;
}