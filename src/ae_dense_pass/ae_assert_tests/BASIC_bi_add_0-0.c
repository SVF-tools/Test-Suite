#include "stdbool.h"
extern void svf_assert(bool);


int main(){
    int x = -1; // 10000000001
    x += 3; // 0000000011
    svf_assert(x == 2); // signed 0000000010  unsigned 100000010
    return 0;
}