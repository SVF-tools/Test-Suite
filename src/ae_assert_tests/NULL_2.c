#include "stdbool.h"
#include <stdlib.h>
extern void svf_assert(bool);

int main() {
    int value = 10;
    int *ptr = &value;
    svf_assert(ptr != NULL);
    return 0;
}
