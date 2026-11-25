/*
 * A Store source can become a non-pointer object representative after Copy
 * SCC merging. The inherited Store must still write target into other.
 * Regression for SVF-tools/SVF#1944.
 */
#include "aliascheck.h"

char target;
void *box[1];
void *other;
void **holder = &other;

int main(int argc, char **argv)
{
    *(void **)&box = &target;
    *(argc ? holder : (void **)&box) = *(void **)&box;
    MAYALIAS(other, &target);
    return 0;
}
