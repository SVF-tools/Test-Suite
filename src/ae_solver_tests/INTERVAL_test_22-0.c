#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>

int main() {
    int a;
    int b = a;
    for(int i = 0; i < 3; i++) {
        b = b * a;
    }
    svf_assert(b >= 0);
}