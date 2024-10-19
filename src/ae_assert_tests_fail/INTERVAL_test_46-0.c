#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int count = 0;
int result = 0;

void foo();
void bar();

void foo(int limit) {
    if(count < limit) {
        result = count + 1;
        count++;
        bar(limit);
    }
    return;
}

void bar(int limit) {
    if(count < limit) {
        result = count - 1;
        count++;
        foo(limit);
    }
    return;
}

int main() {
    int limit;
    if(limit > 0) {
        foo(limit);
        if(limit % 2 == 1) {
            svf_assert(result == limit);
        }
        else {
            svf_assert(result == limit - 2);
        }
    }
    else {
        svf_assert(result == 0);
    }
}
