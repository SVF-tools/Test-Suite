#include "stdbool.h"
extern void svf_assert(bool);
int no_main_CAST_zext() {
    unsigned char size = 255;
    int c = size + 1;
    svf_assert(c == 256);
}