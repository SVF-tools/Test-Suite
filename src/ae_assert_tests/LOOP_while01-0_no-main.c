#include "stdbool.h"
extern void svf_assert(bool);

int no_main_LOOP_while01_0(){
    int x;
    x=1;
    while(x<5) {
        x++;
    }
    svf_assert(x == 5);
    return 0;
}