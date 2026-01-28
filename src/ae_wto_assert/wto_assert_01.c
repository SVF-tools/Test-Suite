/*
 * WTO Assert Test 01: Basic two-branch case with precise constraint
 *
 * This test demonstrates the WTO algorithm behavior where the else block
 * is visited twice with different abstract states:
 * 1) First visit with constraint (a <= 5), assert fails because a:[-oo, 5], res:[-oo, +oo]
 * 2) Second visit with constraint NOT(a > 5 && a < 7), a becomes [-oo, +oo],
 *    under which assert succeeds because a:[-oo, +oo], res:[-oo, +oo]
 *
 * Expected: svf_assert(a == 6) should PASS (a is precisely 6 in the if branch)
 *           svf_assert_eq(a, res) should PASS (after joining states, both are top)
 */

#include "svf_assert.h"

int main() {
    int a = rand();

    if (a > 5 && a < 7) {
        /* In this branch: a must be exactly 6 (the only integer in (5, 7)) */
        svf_print(a, "a value in if branch");
        svf_assert(a == 6);
    }
    else {
        /* First visit: a <= 5, so a:[-oo, 5]
         * Second visit: NOT(a > 5 && a < 7) = (a <= 5 || a >= 7), joined with first gives [-oo, +oo]
         * After WTO joins both visits, a becomes [-oo, +oo]
         */
        int res = rand();
        svf_assert_eq(a, res);  /* Both are [-oo, +oo], so this should pass */
    }

    return 0;
}
