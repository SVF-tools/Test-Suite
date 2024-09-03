#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);

int main(){
    int x, y;
    x=1;
    while(x<5) {
        for (y = 0; y < 3; ++y)
            x++;
        svf_print(x, "x");
    }
    svf_print(x, "x");
    svf_assert(x == 7);
    return 0;
}