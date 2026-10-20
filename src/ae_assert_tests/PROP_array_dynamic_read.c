#include <stdbool.h>

extern void svf_assert(bool);
extern void svf_print(int, const char*);

int main(int argc, char** argv)
{
    int a[2][2] = {{1, 2}, {3, 4}};
    a[1][1] = 8;
    int index = argc > 1 ? 1 : 0;
    int value = a[1][index];
    // The dynamic read can see 3 or 8, including the precise sub-Obj write.
    svf_print(value, "dynamic-array-value");
    svf_assert(value >= 3 && value <= 8);
    svf_assert(a[0][0] == 1);
    return 0;
}
