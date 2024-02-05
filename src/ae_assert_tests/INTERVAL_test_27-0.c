#include "stdbool.h"
extern void svf_assert(bool);
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    srand(time(0));
	int randomNumber = rand() % 128;
    char ch = randomNumber;
    if (isdigit(ch)) {
		svf_assert(randomNumber >= 48 && randomNumber <= 57);
    }
    else {
		svf_assert(randomNumber < 48 || randomNumber > 57);
	}
}
