#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int no_main_INTERVAL_test_36_1_0() {
    int* i = malloc(4 * sizeof(int));
    int ar[4] = {1, 2, 3, 5};
    int a = rand();
    ar[3] = a;
    memcpy(i, ar, 4 * sizeof(int));
    if (i[3] > 5) {
        svf_assert(i[3] > 5);
    }
    else {
        svf_assert(i[3] <= 5);
    }    
}
