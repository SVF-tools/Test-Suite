#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int count = 0;

int sum(int i) {
    count++;
    if (i != 0) {
        return i + sum(i - 1);
    }
    else {
        return i;
    }
}

int main() {
    int i;
    if(i >= 0) {
        sum(i);
        svf_assert(count == i + 1);
    }
}