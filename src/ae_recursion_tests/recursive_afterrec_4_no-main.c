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

int no_main_recursive_afterrec_4(){
    f(1000);

    svf_assert(g == 3);
}