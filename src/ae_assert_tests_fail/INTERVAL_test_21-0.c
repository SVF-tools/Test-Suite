#include "stdbool.h"
extern void svf_assert(bool);
extern void set_value(int, int, int);
extern void svf_print(int, char*);
#include <assert.h>

int main() {
    int a;
    set_value(a, 0, 5);
    int b = a;
    for(int i = 0; i < 10; i++) {
        if(a == 10) {
            break;
        }
        a++;
    }
    svf_print(a, "a");
    if(b >= 0 && b <= 10) {
        svf_assert(a == 10);
    }
    else {
        svf_assert(a = b + 10);
    }

}