#include <stdbool.h>

extern void svf_assert(bool);

struct Pair
{
    int left;
    int right;
};

int main(void)
{
    struct Pair pair = {1, 2};
    pair.left = 7;
    // A field update must not overwrite its sibling or resurrect left=1.
    svf_assert(pair.left == 7);
    svf_assert(pair.right == 2);
    return 0;
}
