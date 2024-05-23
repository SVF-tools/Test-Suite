#include "stdbool.h"
#include <stdlib.h>
extern void svf_assert(bool);

int main() {
    int *ptr = NULL;
    svf_assert(ptr == NULL);
    return 0;
}
