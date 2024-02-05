#include "stdbool.h"
extern void svf_assert(bool);

int main() {
    int a; //a = [-INF, INF]
    int b = 1;
    b = a - b;
    if (a > 5) { //a = [6, INF]
        svf_assert(b <= -5);
    }
    else {
        svf_assert(b > -5);
    }    
}