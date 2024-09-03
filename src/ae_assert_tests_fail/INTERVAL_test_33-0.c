#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  
#include <math.h>  
    
int digitCount(int i) {  
    int counter = 0;
    counter = (i == 0)? 1 : log10(i) + 1;   
    return counter;  
}  

int main() {
    srand(time(0));
	int randomNumber = rand() % 999;
    int counter = digitCount(randomNumber);
    svf_assert(counter >= 1 && counter <= 3);
}