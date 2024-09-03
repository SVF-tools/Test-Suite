#include "stdbool.h"
#include <stdlib.h>
extern void svf_assert(bool);

int main() {
    int *ptr = NULL;
    bool isNullDereference = false;

    if (ptr == NULL) {
        isNullDereference = true;
    }

    svf_assert(isNullDereference);
    return 0;
}
