#include <stdio.h>

extern void UNSAFE_LOAD(void *ptr);

union Data {
    int* int_ptr;
    float* float_ptr;
};

int main() {
    union Data data;
    data.int_ptr = NULL;
    UNSAFE_LOAD(data.int_ptr);  // This will trigger a null pointer dereference

    return 0;
}
