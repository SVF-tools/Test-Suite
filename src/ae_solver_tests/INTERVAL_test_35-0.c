#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  

int counter = 0;

long factorial(int i) {
    counter++;
    if(i <= 1) {
        return 1;
    }
    return i * factorial(i - 1);
}

int main() {
    int i;
    long f = factorial(i);
    svf_assert(counter == i);
}
