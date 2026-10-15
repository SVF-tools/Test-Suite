#include <stdbool.h>

extern void svf_assert(bool);
extern void svf_print(int, const char*);

int main(void)
{
    int i = 0;
    while (i < 4)
        i = i + 1;
    // Widening/narrowing and the exit constraint should establish i=4.
    svf_print(i, "loop-exit-i");
    svf_assert(i == 4);
    return 0;
}
