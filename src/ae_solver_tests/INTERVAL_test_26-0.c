#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>

int main() {
    int a; //a = [-INF, INF]
    a = a % 5;
    svf_assert(a >= 0 && a < 5); //if a is a negative number, this assertion does not hold
}