#include <string.h>
#include "stdbool.h"
#include <stdio.h>
#define ALLOCA alloca

extern void svf_assert(bool);
extern void svf_print(int, char*);

int main() {
    char data;
    data = ' ';
    /* POTENTIAL FLAW: Use a value input from the console */
    fscanf(stdin, "%c", &data);
    /* POTENTIAL FLAW: Adding 1 to data could cause an overflow */
    svf_print(data, "data");
    char result = data + 1;
    svf_print(result, "result");
    svf_assert(result <= 255);
}