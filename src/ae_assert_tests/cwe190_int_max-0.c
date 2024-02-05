//
// Created by Jiawei Wang on 2/11/22.
//
#include <string.h>
#include "stdbool.h"
#include <stdio.h>
#define ALLOCA alloca

extern void svf_assert(bool);

int main() {
    int data;
    /* Initialize data */
    data = 0;
    /* POTENTIAL FLAW: Use the maximum value for this type */
    data = 2;
    /* POTENTIAL FLAW: if (data*2) > INT_MAX, this will overflow */
    int result = data * 2;
    svf_assert(data < 2147483647);
}