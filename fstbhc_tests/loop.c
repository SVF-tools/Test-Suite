#include "aliascheck.h"

// Two objects generated in a loop
// without an allocation wrapper.

int main(int argc, char *argv[]) {
    int *i;
    float *f;

    // Condition doesn't matter; it's static analysis (no opt!).
    while (argc-- < 2) {
        void *m = malloc(4);
        if (argc) {
            i = m;
        } else {
            f = m;
        }
    }

    TBHC_NOALIAS(i, f);
}
