#include "stdbool.h"
extern void svf_assert(bool);
int main(){
    int x=1;
    int y=1;
    svf_assert(x == y);
    return 0;
}