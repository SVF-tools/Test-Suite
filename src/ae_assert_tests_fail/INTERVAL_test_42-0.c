#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int count = 0;

int foo(int i) {  
    count++;
    if(i == 0) {  
        return 0;
    }  
    else {  
        return foo(i - 1);
    }  
}

int main() {
    int i;
    if(i >= 0) {
        foo(i);
        svf_assert(count == i + 1);
    }
}
