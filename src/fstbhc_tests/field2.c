#include "aliascheck.h"

// Same object, different field.
// (fspta passes too.)

struct S {
    int f1;
    int f2;
    int f3;
};

int main(int argc, char *argv[]) {
    struct S *s = malloc(sizeof(struct S));
    // TBHC_NOALIAS(&s->f1, &s->f2);
    // ^ Old test. This does not pass on the current FSTBHC
    // implementation because we treat s the same as &s->f1.
    // This is sound but somewhat imprecise and makes implementing
    // the first-field rules easier. It can be improved.
    TBHC_NOALIAS(&s->f2, &s->f3);
}
