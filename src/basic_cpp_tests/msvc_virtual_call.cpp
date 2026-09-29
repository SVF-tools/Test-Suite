/*
 * MSVC C++ Virtual Call & VTable Layout Test for SVF WPA/CHA
 * Exercises MSVC C++ mangling (??_7, ??0, ??1) and MSVCABI resolution.
 */

extern "C" void print_msg(const char* msg);

class Base {
public:
    Base() {}
    virtual ~Base() {}
    virtual void foo() {
        print_msg("Base::foo");
    }
};

class Derived : public Base {
public:
    Derived() {}
    virtual ~Derived() {}
    virtual void foo() override {
        print_msg("Derived::foo");
    }
};

int main() {
    Base* b = new Derived();
    b->foo();
    delete b;
    return 0;
}
