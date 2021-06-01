void checkType(void* clz, char* ty){}

class A {
        public:
        A(){}
};

class B : public A {
        public:
        B(){}
};

class C : public B {
        public:
        C(){}
};

int main(void) {
    A *a = new A();
    checkType(a,"A");
}

