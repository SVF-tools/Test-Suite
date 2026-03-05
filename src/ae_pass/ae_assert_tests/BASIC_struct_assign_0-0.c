#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>


extern void __VERIFIER_error (void);
extern void __VERIFIER_assume (int);
extern void svf_assert(bool);
#define assume __VERIFIER_assume


typedef struct Struct {
    int x;
    int y;
} Struct;

int main() {
    Struct a;
    int *p = &a.y;
    a.y = 10;
    svf_assert(*p == 10);
    return 0;
}
