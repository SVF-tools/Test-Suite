#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);
int main() {
    float f = 3.14;
    unsigned int ui = (unsigned int)f; // fptoui
    svf_print(ui, "UI");
    svf_assert(ui == 3);
    return 0;
}