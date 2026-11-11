/*
 * A Copy SCC can choose the non-pointer box object as the representative of
 * a pointer-valued Load result. Reading box afterward must still reach target.
 * Regression for SVF-tools/SVF#1944.
 */
#include "aliascheck.h"

void *box[1];
char target;
void *other = &target;
void **holder = &other;

int main(int argc, char **argv)
{
    *(void **)&box = *(argc ? holder : (void **)&box);
    MAYALIAS(*(void **)&box, &target);
    return 0;
}
