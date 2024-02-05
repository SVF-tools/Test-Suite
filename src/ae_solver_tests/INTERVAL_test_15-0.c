#include "stdbool.h"
extern void svf_assert(bool);

int main() {
    int a; //a = [-INF, INF]
    a = a % 5;
    if (a >= 0) {
        svf_assert(a >= 0 && a < 5);
    }
}