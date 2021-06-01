#include "aliascheck.h"

// First field is actually float, not int (it's static).
struct S {
    static int i;
    float f;
};

int main(void) {
    // *Can't* downcast int->S.
    int *i = (int *)malloc(sizeof(struct S));
    *i;
    struct S *s1 = (struct S *)i;
    TBHC_NOALIAS(&(s1->i), i);

    // *Can* downcast int->S.
    float *f = (float *)malloc(sizeof(struct S));
    *f;
    struct S *s2 = (struct S *)f;
    TBHC_MUSTALIAS(&(s2->f), f);
}
