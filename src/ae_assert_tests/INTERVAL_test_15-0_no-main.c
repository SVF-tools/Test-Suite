#include "stdbool.h"
extern void svf_assert(bool);

int no_main_INTERVAL_test_15_0() {
    int a; //a = [-INF, INF]
    a = a % 5;
    if (a >= 0) {
        svf_assert(a >= 0 && a < 5);
    }
}