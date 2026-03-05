#include "stdbool.h"
extern void svf_assert(bool);

int g;

void f(int n) {
    if (n<3){
        g = 3;
        return;
    }
    n--;
    f(n);
}

int main(){
    f(4);

    svf_assert(g == 3);
}