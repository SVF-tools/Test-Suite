#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

struct testStruct {
    int a;
};  

int main() {
    struct testStruct* i = malloc(4 * sizeof(struct testStruct));
    if (i[3].a > 5) {
        svf_assert(i[3].a > 5);
    }
    else {
        svf_assert(i[3].a <= 5);
    }    
}
