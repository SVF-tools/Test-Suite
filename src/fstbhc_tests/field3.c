#include "aliascheck.h"

// Returns field from function.

struct S {
    int f;
};

int *foo(struct S *s) {
    return &s->f;
}

int main(void) {
    struct S *s = malloc(sizeof(struct S));
    s->f = 300;
    int *i = foo(s);
    TBHC_MUSTALIAS(&s->f, i);
}
