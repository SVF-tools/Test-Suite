#include <stdbool.h>
#include <stdlib.h>

extern void svf_assert(bool);
extern void svf_assert_eq(int, int);
extern void svf_print(int, const char*);

static int* allocate(void)
{
    return malloc(sizeof(int));
}

int main(int argc, char** argv)
{
    int expected = argc > 1 ? 1 : 2;
    int* a = allocate();
    int* b = allocate();
    *a = 1;
    *b = 2;
    // The singleton allocation-site Obj summarizes two distinct allocations.
    svf_print(*a, "heap-a");
    svf_print(*b, "heap-b");
    svf_assert(*a >= 1 && *a <= 2 && *b >= 1 && *b <= 2);
    svf_assert_eq(*a, expected);
    svf_assert_eq(*b, expected);
    free(a);
    free(b);
    return 0;
}
