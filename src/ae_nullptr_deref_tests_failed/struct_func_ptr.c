#include <stdio.h>

struct Operations {
    void (*op_function)(int); // function ptr
};

int main() {
    struct Operations ops;
    ops.op_function = NULL;
    ops.op_function(10);  // Triggers a null pointer dereference
}