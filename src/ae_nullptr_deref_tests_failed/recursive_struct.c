#include <stdio.h>
#include <wchar.h>

extern void UNSAFE_LOAD(void *ptr);

struct S {
    int *intPtr;
    char *charPtr;
    int64_t *int64Ptr;
    wchar_t *wcharPtr;
};

void recursive_function(struct S s, int depth) {
    if (depth > 0) {
        // Do nothing and keep calling itself
        recursive_function(s, depth - 1);
    } else {
        // Base case reached, dereferencing NULL pointer
        UNSAFE_LOAD(s.intPtr);
        UNSAFE_LOAD(s.charPtr);
        UNSAFE_LOAD(s.int64Ptr);
        UNSAFE_LOAD(s.wcharPtr);
    }
}

int main() {
    struct S myStruct;
    myStruct.intPtr = NULL;
    myStruct.charPtr = NULL;
    myStruct.int64Ptr = NULL;
    myStruct.wcharPtr = NULL;
    
    recursive_function(myStruct, 3);
    return 0;
}