#include "stdbool.h"
#include <stdlib.h>
extern void svf_assert(bool);

int main() {
    int *a[3][3] = {NULL};

    bool isNull = (a[0][0] == NULL);
    svf_assert(isNull);

    return 0;
}
