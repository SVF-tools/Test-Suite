#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);

int demo(int a) {
    if (a >= 10000)
        return a;
    demo(a+1);
}

int main() {
    int result = demo(0);
    svf_print(result, "result");
    svf_assert(result == 10000);
}

// TOP: [-oo, +oo]
// WIDEN_ONLY: [10000, +oo]
// WIDEN_NARROW: [10000, 10000]