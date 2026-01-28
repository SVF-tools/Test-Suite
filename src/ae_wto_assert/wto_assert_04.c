/*
 * WTO Assert Test 04: Multiple exclusive ranges
 *
 * This test has multiple mutually exclusive conditions that lead to
 * different precise values, testing the WTO's ability to track
 * distinct abstract states through different control flow paths.
 *
 * Expected: All assertions should PASS with proper constraint propagation
 */

#include "svf_assert.h"

int main() {
    int a = rand();
    int result = 0;

    if (a > 0 && a < 2) {
        /* a is exactly 1 */
        result = 100;
        svf_assert(a == 1);
    }
    else if (a > 4 && a < 6) {
        /* a is exactly 5 */
        result = 200;
        svf_assert(a == 5);
    }
    else if (a > 9 && a < 11) {
        /* a is exactly 10 */
        result = 300;
        svf_assert(a == 10);
    }
    else {
        /* a is in one of: [-oo, 0], [2, 4], [6, 9], [11, +oo] */
        int b = rand();
        /* After WTO joins all visits to else block, both a and b become top */
        svf_assert_eq(a, b);
        result = -1;
    }

    /* result should be one of: 100, 200, 300, or -1 */
    /* After joining all paths, result: [-1, 300] which includes all possibilities */

    return 0;
}
