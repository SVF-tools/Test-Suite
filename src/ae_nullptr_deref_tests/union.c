#include <stdio.h>

union Data {
    int* int_ptr;
    float* float_ptr;
};

int main() {
    union Data data;
    data.int_ptr = NULL;
    int value = *(data.int_ptr);  // This will trigger a null pointer dereference

    return 0;
}
