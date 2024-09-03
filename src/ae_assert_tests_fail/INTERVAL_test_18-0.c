#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>

int loop(int a) {
    int result = 0;
    int output = 0;
    for(int i = 1; i <= a; i++) {
        if(i % 2 != 0) {
            continue;
        }
        output++;
    }
    return output;
}

int main() {
    int a;
    int b = a;
    int output = 0;
    if(a > 0) {
        output = loop(a);
        svf_assert(output == b/2);
    }
    else {
        svf_assert(output == 0);
    }
}