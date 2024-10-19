#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int digitCount(int i) {  
    int counter = 0;
    while(true) { 
        i = i/10;  
        counter++;  
        if(i == 0) {
            break;
        }  
    }
    return counter;
}  

int main() {
    srand(time(0));
	int randomNumber = rand() % 999;
    int counter = digitCount(randomNumber);
    svf_assert(counter >= 1 && counter <= 3);
}
