#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int foo() {
    int i = 0;
    bool a = true;
    do {
        i++;
    } while(i < 5 && a);
    return i;
}

int bar() {
    int i = 0;
    bool a = false;
    do {
        i++;
    } while(i < 5 && a);
    return i;
}

int main() {
	srand(time(0));
	int a = rand() % 2;
    int b = (a) ? foo() : bar();
    if(a) {
        svf_assert(b == 5);
    }
    else {
        svf_assert(b == 1);
    }
}

