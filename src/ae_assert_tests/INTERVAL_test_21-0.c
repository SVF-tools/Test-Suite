#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>

int main() {
    int a;
    int b = a;
    for(int i = 0; i < 10; i++) {
        if(a == 10) {
            break;
        }
        a++;
    }
    if(b >= 0 && b <= 10) {
        svf_assert(a == 10);
    }
    else {
        svf_assert(a = b + 10);
    }

}