#include "stdbool.h"
extern void svf_assert(bool);

void f(int);
void f2(int);

int g;

void f(int n) {
    if (n<3){
        g = 3;
        return;
    }
    n--;
    f2(n);
}

void f2(int n) {
    if (n<3){
        g = 3;
        return;
    }
    n--;
    f(n);
}

int main(){
    f(10);

    svf_assert(g == 3);
}