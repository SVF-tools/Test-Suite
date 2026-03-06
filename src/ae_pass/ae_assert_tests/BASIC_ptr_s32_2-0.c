//
// Created by Jiawei Wang on 6/30/22.
//
#include "stdbool.h"
extern void svf_assert(bool);

#define ALLOCA alloca

int main() {
    int a[3] = {1,2,3};
    int* p = (int *)ALLOCA((4)*sizeof(int)); // INT_MIN , INT_MAX
    memcpy(p , a, 3*sizeof(int));
}
