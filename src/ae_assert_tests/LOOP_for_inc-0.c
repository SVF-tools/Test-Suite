#include "stdbool.h"
extern void svf_assert(bool);
int main() {
    int i = 0;
    for (i = 0; i < 5; i++) {
        i++;
    }
    svf_assert(i == 6);
}
