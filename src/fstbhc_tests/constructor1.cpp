#include "aliascheck.h"

int *global = nullptr;

class A {
public:
    int x;

    A() {
        foo();
    }

    virtual void foo() {
        global = &this->x;
    }
};

class B : public A {
public:
    B() { }

    // Never called.
    virtual void foo() override {
        global = nullptr;
    }
};

int main(void) {
    B *b = new B();
    TBHC_MAYALIAS(global, &b->x);
}

