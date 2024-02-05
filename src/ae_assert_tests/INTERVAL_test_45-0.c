#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int baseConversion(int i, int base) {
    if(i == 0) {
        return 0;
    }
    return i % base + 10 * baseConversion(i / base, base);
}

int main() {
    srand(time(0));
    int randomNumber = rand() % 999;
    //octal value
    int i = baseConversion(randomNumber, 8);
    svf_assert(i >= 0 && i <= 1746);
}
