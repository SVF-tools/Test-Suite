
#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);
int main() {
    int a = 10;
    int b = 5;
    int c = a / b;
    int d = a % b;
    svf_print(c, "c");
    svf_print(d, "d");
    svf_assert(c == 2 && d == 0);
    return 0;
}