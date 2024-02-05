#include "stdbool.h"
extern void svf_assert(bool);
int main() {
    int i = 0;
    int j = 0;
    for (i = 0; i < 5; i++) {
        if (j==3) break;
        j++;
    }
    svf_assert(i == 3);
}
