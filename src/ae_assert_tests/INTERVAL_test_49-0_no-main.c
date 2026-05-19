#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>

void foo(int* i) {
    LOOP:
    *i = *i + 1;
    if(*i < 10) {
        goto LOOP;
    }
}

int no_main_INTERVAL_test_49_0() {
    int i;
    foo(&i);
    svf_assert(i >= 10);
}
