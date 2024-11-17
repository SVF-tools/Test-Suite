#include "stdbool.h"
extern void svf_assert(bool);

int main(){
    int x;
    x=128;
    while(x>4) {
        x/=2;
    }
    svf_assert(x == 4);
    return 0;
}