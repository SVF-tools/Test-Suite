#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int main() {
	int a = 0;
    int b = 0;
    int c;
    LOOP:
    if(a < c) {
        a++;
        b = b + 2;
        goto LOOP;
    }
    svf_assert(a == c);
    svf_assert(b == a * 2);
}