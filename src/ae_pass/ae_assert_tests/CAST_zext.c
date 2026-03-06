#include "stdbool.h"
extern void svf_assert(bool);
int main() {
    unsigned char size = 255;
    int c = size + 1;
    svf_assert(c == 256);
}