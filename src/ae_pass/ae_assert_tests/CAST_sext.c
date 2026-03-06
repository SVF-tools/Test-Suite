#include "stdbool.h"
extern void svf_assert(bool);

int main() {
    signed char size = -1;
    int c = size;
    svf_assert(c == -1);
}