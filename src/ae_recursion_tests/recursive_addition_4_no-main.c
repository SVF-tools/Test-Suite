#include "stdbool.h"
extern void svf_assert(bool);

int addition(int m, int n) {
    if (n == 0) {
        return m;
    }
    if (n > 0) {
        return addition(m+1, n-1);
    }
    if (n < 0) {
        return addition(m-1, n+1);
    }
}

int no_main_recursive_addition_4(){
    int result = addition(0, 0);

    svf_assert(result == 0);
}