#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int sumDigits(int i) {
    static int sum = 0;
    if(i!=0) {
        sum = sum + (i % 10); 
        sumDigits(i/10);
    }
    return sum;
}

int main() {
    srand(time(0));
	int randomNumber = rand() % 999;
    int i = sumDigits(randomNumber);
    svf_assert(i >= 0 && i <= 26);
}
