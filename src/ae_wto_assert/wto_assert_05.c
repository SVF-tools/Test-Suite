/*
 * WTO Assert Test 05: Combination of loop and branching
 *
 * This test combines both loop analysis (requiring widening/narrowing)
 * and branching with precise constraints, testing the full WTO capability.
 *
 * Expected: All assertions should PASS after proper WTO analysis
 */

#include "svf_assert.h"

int main() {
    int n = rand();
    int count = 0;

    /* First, process with a loop */
    int i = 0;
    while (i < 5) {
        count = count + 1;
        i = i + 1;
    }
    /* After loop: i >= 5,*/
    svf_assert(i >= 5);
    svf_assert(count >= 0);

    /* Now branch based on external input */
    if (n > 100 && n < 102) {
        /* n is exactly 101 */
        svf_print(n, "n value when 100 < n < 102");
        svf_assert(n == 101);

        /* count should still be >= 5 from the loop */
        svf_assert(count >= 0);
    }
    else {
        /* Multiple visits to this else block with different n constraints:
         * Visit 1: n <= 100
         * Visit 2: n >= 102
         * After join: n is top [-oo, +oo]
         */
        int m = rand();
        svf_assert_eq(n, m);  /* Both are top, should pass */

    }

    return 0;
}
