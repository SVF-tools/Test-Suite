#include "stdbool.h"
#include "stdio.h"

extern void svf_assert(bool);

int id(int x);
int id2(int x);

int id(int x) {
    if (x==0) return 0;
    int ret = id2(x-1) + 1;
    if (ret > 5) return 5;
    return ret;
}

int id2(int x) {
    if (x==0) return 0;
    int ret = id(x-1) + 1;
    if (ret > 5) return 5;
    return ret;
}

int main(){
    int x;
    scanf("%ud", &x);

    int res = id(x);
    svf_assert(res <= 5);
}