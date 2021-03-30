/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"

int x, y; int *p = &x; int *q = &y;
int **pp = &p; int**qq = &q;

void foo() {
     TBHC_NOALIAS(*pp, *qq);
}
void bar() {
     qq = &q;
     q = &x;
}
int main() {
    foo();
    bar();
    TBHC_MUSTALIAS(*pp, *qq);
}

