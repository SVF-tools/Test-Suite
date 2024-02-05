#include <string.h>
#include "stdbool.h"
#include <stdio.h>
#define ALLOCA alloca

extern void svf_assert(bool);

int main() {
    char data;
    data = ' ';
    /* POTENTIAL FLAW: Use a value input from the console */
    fscanf(stdin, "%c", &data);
    /* POTENTIAL FLAW: Adding 1 to data could cause an overflow */
    char result = data + 1;
    svf_assert(result <= 255);
}