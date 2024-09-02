#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p;
    int i = 0;
    while (i < 100) {
        if (i == 50) {
            p = NULL; // <⊥, ⊥>
        }
        else {
            p = malloc(sizeof(int)); // <⊥, [0x7f...]>
        }
        *p = 42; // <⊥, ⊥> join with <⊥, [0x7f...]> => <⊥, [0x7f...]> NOT NUll
        i++;
    }

    return 0;
}
