#include "stdbool.h"
extern void svf_assert(bool);
int main() {
    int si = -42;
    float f = (float)si; // sitofp
    svf_assert(f == -42.0f);
    return 0;
}