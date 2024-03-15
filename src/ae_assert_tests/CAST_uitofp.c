#include "stdbool.h"
extern void svf_assert(bool);
int main() {
    unsigned int ui = 42;
    float f = (float)ui; // uitofp
    svf_assert(f == 42.0f);
    return 0;
}