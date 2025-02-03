#include "stdbool.h"
extern void svf_assert(bool);

int main(){
    int x;
    x=10;
    while(x>0) {
        x--;
    }
    svf_assert(x == 0);
    return 0;
}