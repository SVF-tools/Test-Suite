#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>

int loop(int a) {
    int output = 0;
    int i = 1;
    while(true) {    
        if(i % 2 == 0) {
            output++;
        }
        if(i == a) {
            break;
        }
        i++;
    }
    return output;
}

int main() {
    int a;
    int output = 0;
    if(a > 0) {
        output = loop(a);
        svf_assert(output == a/2);
    }
    else {
        svf_assert(output == 0);
    }
}