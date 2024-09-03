#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int count = 0;

int fib(int i) {
    count++;
    if(i == 0) {
        return 0;
    }
    if(i == 1) {
        return 1;
    }
    return fib(i - 1) + fib(i - 2);
}

int main() {
    int i;
    if(i >= 0) {
        fib(i);
        svf_assert(count == 2 * fib(i + 1) - 1);
    }
}
