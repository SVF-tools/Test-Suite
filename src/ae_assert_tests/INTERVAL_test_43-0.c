#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int count = 0;

int power(int a, int b) {
    count++;
    if(b < 0) {
        return 0;
    }
    else if(b == 0) {
        return 1;
    }
    else {
        return(a * power(a, b - 1));
    }
}
int main() {
    int a;
    int b;
    power(a, b);
    if(b > 0) {
        svf_assert(count == b + 1);
    }
    else {
        svf_assert(count == 1);
    }
}
