#include "stdbool.h"
#include "math.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);
extern void set_value(int, int, int);

void foo(int* i) {
    *i = *i + 1;
    if(*i < 10) {
        foo(i);
    }
}

int main() {
    int i;
    set_value(i, 0, 5);
    foo(&i);
    svf_assert(i >= 0); // now we cannot handle recursive, it should be changed later.
}