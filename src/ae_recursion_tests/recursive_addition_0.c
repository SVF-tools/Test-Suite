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

int main(){
    int result = addition(10, 5);

    svf_assert(result >= 10);
}