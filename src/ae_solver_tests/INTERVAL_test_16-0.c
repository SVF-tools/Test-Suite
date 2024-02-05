#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>

void foo(int* i) {
    *i = *i + 1;
    if(*i < 10) {
        foo(i);
    }
}

int main() {
    int i;
    foo(&i);
    svf_assert(i >= 10);
}