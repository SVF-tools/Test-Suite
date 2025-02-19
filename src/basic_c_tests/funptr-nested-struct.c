extern void MAYALIAS(void*,void*);
struct interesting {
        int dummy;
        void (*f1)(int*);
        void (*f2)(int*);
};

struct nested_ptr {
        int dummy;
        struct interesting* ptr;
};

int g;
void f1(int* a){ MAYALIAS(a, &g);}
void f2(int* a){ MAYALIAS(a, &g);}

struct interesting i1 = {
        .f1 = f1,
        .f2 = f2
};

struct nested_ptr n1 = {
        .ptr = &i1
};

void test_ptr() {
        struct nested_ptr tmp = n1;
        struct interesting interesting_stub = *tmp.ptr;
        interesting_stub.f1(&g);
        interesting_stub.f2(&g);
}
