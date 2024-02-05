#include "stdbool.h"
extern void svf_assert(bool);

int main() {
    int a; //a = [-INF, INF]
    int b = 10;
    b = b / a;
    if(a > 0 && a <= 5) {
        svf_assert(b >= 2);
    }
}