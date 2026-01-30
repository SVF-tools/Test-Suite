/*
 * WTO Assert Test 03: Loop with widening
 *
 * This test includes a loop that triggers the WTO widening mechanism.
 * The loop counter should be properly widened and then narrowed.
 *
 * Expected: svf_assert should PASS after proper widening/narrowing
 */

#include "svf_assert.h"

int main() {
    int i = 0;
    int sum = 0;

    /* Loop will be analyzed using WTO with widening */
    while (i < 10) {
        sum = sum + i;
        i = i + 1;
    }

    /* After loop: i should be >= 10 (due to loop exit condition) */
    /* With widening, i could be [10, +oo) but after narrowing should be closer to 10 */
    svf_assert(i >= 10);

    /* sum should be non-negative (started at 0, only added non-negative values) */
    svf_assert(sum >= 0);

    return 0;
}
