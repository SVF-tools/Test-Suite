#include "aliascheck.h"

typedef struct {
    int x;
    void (*myfunction)(float *f, long l);
} str;

float globalf = 3.33333;

void foo(float *f, long l) {
    TBHC_NOALIAS(f, &globalf);
}

void bar(float *f, long l) {
    TBHC_MUSTALIAS(f, &globalf);
}

str *spec;

void decode(str *hi) {
    hi->myfunction = bar;
}

int main(int argc, char *argv[]) {
    spec = malloc(5000);
    decode(&spec[argc]);
    (*spec[argc].myfunction)(&globalf, 555);

    float localf;
    foo(&localf, 0);
}
