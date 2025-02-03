#include "stdbool.h"
extern void svf_assert(bool);

int main(){
    int x;
    x=1;
    while(x<128) {
        x*=2;
    }
    svf_assert(x == 128);
    return 0;
}