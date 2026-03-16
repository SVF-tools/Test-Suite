#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);

int main() {
    //int a = 0;
    int a;
    int b = 1;
    scanf("%d", &a); //[-INF, INF] top
    if (a > 5) { //a = [6, INF]
        b = a + b;
        svf_print(b, "b1");
        svf_assert(b > 6); //b = [1, 1] + [6, INF]
    }
    else {
        b = a + b;
        svf_print(b, "b2");
        svf_assert(b <= 6);
    }    
}