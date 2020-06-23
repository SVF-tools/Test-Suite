
#include <stdlib.h>

int g1;
int g2;

void f1(int **pp) {
        *pp = &g1;
}
void f2(int **pp) {
        f1(pp);
            *pp = &g2;
}
int f3() {
        int **pp = malloc(sizeof(int *));
            f2(pp);
                return **pp;
}
int f4() {
        int *p;
            f2(&p);
                return *p;
} 
