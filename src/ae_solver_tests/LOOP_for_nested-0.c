#include "stdbool.h"
extern void svf_assert(bool);
int main() {
    int i = 0;
    int j = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; ++j) {

        }
    }
    svf_assert(i == 5 && j == 3);
}
