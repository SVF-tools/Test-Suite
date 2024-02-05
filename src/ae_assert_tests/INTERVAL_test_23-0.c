#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>

int main () {
    int input;
    int a = input; 
    int b;
    if(b != 0) {
        //"If the quotient a/b is representable, the expression (a/b)*b + a%b shall equal a" - C99 standard
        a = (a / b) * b + a % b;
        svf_assert(a == input);
    }
}