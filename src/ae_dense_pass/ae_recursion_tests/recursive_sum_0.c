#include "stdbool.h"
extern void svf_assert(bool);

int sum(int n, int m) {
    if (n <= 0) {
        return m + n;
    } else {
        return sum(n - 1, m + 1);
    }
}

int main(){
    int a = 0;
    int b = 3;
    int res = sum(a, b);
    svf_assert(res <= 3);
}