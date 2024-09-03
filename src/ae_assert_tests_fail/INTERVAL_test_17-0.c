#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);

int loop(int a) {
    int result = 0;
    int output = 0;
    for(int i = 1; i <= a; i++) {
        if(i % 2 == 0) {
            output++;
        }
    }
    return output;
}

int main() {
    int a;
    int b = a;
    int output = 0;
    if(a > 0) {
        output = loop(a);
        svf_print(output, "output");
        svf_print(b, "b");
        svf_assert(output >= 0);
    }
    else {
        svf_assert(output == 0);
    }
}