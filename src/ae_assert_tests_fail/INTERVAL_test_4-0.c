#include <stdlib.h>
#include "stdbool.h"
extern void svf_assert(bool);

int main() {
	srand(time(0));
	int a = rand() % 5; //[0, 4]
    int b = rand() % 5; //[0, 4]
    int c = a * b;
    if (c == 16) { //a = [6, INF]
        svf_print();
        svf_assert(a == 4 && b == 4);
    }
    else {
        svf_assert(a < 4 || b < 4); 
    }    
}
