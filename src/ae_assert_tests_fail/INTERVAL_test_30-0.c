#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    srand(time(0));
	int randomNumber = rand() % 999;
	int i = printf("Value:%d", randomNumber);
	svf_assert(i >= 7 && i <= 9);
}