#include "aliascheck.h"

class A {
public:
    virtual void foo(int *x, int *y) {
        TBHC_NOALIAS(x, y);
    }
};

class B : public A {
public:
    virtual void foo(int *x, int *y) override {
        TBHC_EXPECTEDFAIL_NOALIAS(x, y);
    }
};

int main(void) {
    int i, j;

    A *a = new A();
    // A::foo::x == &i && A::foo::y == &j
    a->foo(&i, &j);

    B *b = new B();
    if (i) a = (A *)b;
    // A::foo::x == &i, A::foo::y == &j
    // B::foo::x == &i, B::foo::y == &j
    a->foo(&i, &j);
    // B::foo::x == &j, B::foo::y == &i
    // but from the previous call also...
    // B::foo::x == &i, B::foo::y == &j
    b->foo(&j, &i);
}

