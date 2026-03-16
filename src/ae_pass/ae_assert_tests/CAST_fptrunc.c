#include "stdbool.h"
extern void svf_assert(bool);
int main() {
    double d = 1.0;
    float f = (float)d; // fptrunc from double to float
    svf_assert(f == 1.0f);
    return 0;
}