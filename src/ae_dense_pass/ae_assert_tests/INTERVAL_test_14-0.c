#include "stdbool.h"
#include "math.h"
extern void svf_assert(bool);

int main() {
    int a = rand(); //a = [-INF, INF]
    int b = 10;
    if(a > 0 && a <= 5) {
        b = b / a;
        svf_assert(b >= 2);
    }
}