#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

int main() {
	int buffer[58];
    srand(time(0));
	int randomNumber = rand() % 128;
    char ch = randomNumber;
    if (isdigit(ch)) {
		//randomNumber = [48, 57]
		buffer[randomNumber] = 1; //FP
    }
    else {
		//randomNumber < 48 || randomNumber > 57
		buffer[randomNumber] = 1; //TP
	}
}
