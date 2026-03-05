#include "stdbool.h"
#include "math.h"
extern void svf_assert(bool);

int main() {
    int a = rand(); //a = [-INF, INF]
    int b = -2;
    if (a > 5) { //a = [6, INF]
        b = a * b;
        svf_assert(b <= -12);
    }
    else {
        b = a * b;
        svf_assert(b > -12);
    }    
}