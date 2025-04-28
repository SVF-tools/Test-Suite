#include "stdbool.h"
#include "stdio.h"

extern void svf_assert(bool);

unsigned int id(unsigned int x) {
    if (x==0) return 0;
    unsigned int ret = id(x-1) + 1;
    if (ret > 2) return 2;
    return ret;
}

int main(){
    int x;
    scanf("%ud", &x);

    int res = id(x);
    svf_assert(res <= 2);
}