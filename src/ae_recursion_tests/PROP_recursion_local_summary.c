#include <stdbool.h>

extern void svf_assert(bool);
extern void svf_print(int, const char*);

static void update_frame(int depth, int* outer)
{
    int value = depth;
    if (depth == 0)
    {
        *outer = 2;
        // This frame's concrete value is 0, not the caller's updated 2.
        // One context-insensitive stack Obj can summarize both frames.
        svf_print(value, "recursive-inner");
        svf_assert(value <= 2);
    }
    else
    {
        update_frame(depth - 1, &value);
        svf_print(value, "recursive-outer");
        svf_assert(value <= 2);
    }
}

int main(void)
{
    update_frame(1, 0);
    return 0;
}
