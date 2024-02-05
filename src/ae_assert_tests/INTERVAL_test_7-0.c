#include <stdlib.h>
#include "stdbool.h"
extern void svf_assert(bool);

int main() {
	int a = 0;
    int b = 0;
    while(a < 10) {
        a++;
        b = b + 2;
    }
    svf_assert(a == 10);
    svf_assert(b == 20);    
}