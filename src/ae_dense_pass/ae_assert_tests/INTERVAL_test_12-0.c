#include "stdbool.h"
#include "math.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);
int main() {
    int a = rand(); //a = [-INF, INF]
    int b = 1;
    if (a > 5) { //a = [6, INF]
        b = a - b;
        svf_assert(b >= 5);
    }
    else {
        b = a - b;
        svf_assert(b <= 4);
    }    
}