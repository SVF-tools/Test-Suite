#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, const char*);
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    srand(time(0));
	int r = rand() % 128;
    char a = (char)r; //random ascii character
    if (a >= 'a' && a <= 'z') {
        int a_as_int = (int)a;
        svf_print(a_as_int, "a");
        svf_assert(a_as_int >= 97 && a_as_int <= 122);
    }
}