#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);

int main() {
    int i = 0;
    int j = 0;
    for (i = 0; i < 5; i++) {
        if (j==1) break;
        j++;
    }
    svf_print(i, "i");
    svf_assert(i == 1);
}
