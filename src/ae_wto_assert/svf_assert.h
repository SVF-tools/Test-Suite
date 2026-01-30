/*
 * SVF Assertion API for Abstract Execution Tests
 * These functions are handled specially by SVF's Abstract Interpretation engine
 */

#ifndef SVF_ASSERT_H
#define SVF_ASSERT_H

#include <stdlib.h>

/* External declarations for SVF assertion functions */
extern void svf_assert(int condition);
extern void svf_assert_eq(int a, int b);
extern void svf_print(int value, const char* text);

/* Helper to get a random/unknown value for abstract interpretation */
static inline int get_unknown_value(void) {
    return rand();
}

#endif /* SVF_ASSERT_H */
