#include "stdbool.h"
extern void svf_assert(bool);
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    srand(time(0));
	int r = rand() % 128;
    char a = (char)r; //random ascii character
    int a_as_int = (int)a;
    if (a >= 'a' && a <= 'z') {
        svf_assert(a_as_int >= 97 && a_as_int <= 122);
    }
}