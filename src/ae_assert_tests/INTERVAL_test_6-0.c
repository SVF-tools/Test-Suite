#include <stdlib.h>
#include "stdbool.h"
extern void svf_assert(bool);

int main() {
	int a = 0;
    while(a < 10) {
        a++;
    }
    svf_assert(a == 10);    
}