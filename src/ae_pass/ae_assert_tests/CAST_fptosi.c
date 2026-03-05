#include "stdbool.h"
extern void svf_assert(bool);
int main() {
    float f = -3.14;
    int si = (int)f; // fptosi
    svf_assert(si == -3);
    return 0;
}