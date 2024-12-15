#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

struct Operations {
    void (*op_function)(int); // function ptr
};

int main() {
    struct Operations *ops = NULL;
    UNSAFE_LOAD(&ops->op_function);  // Triggers a null pointer dereference
}