//
// Created by Jiawei Wang on 4/27/22.
//

#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);
int add(int a) {
    return a + 1;
}
int main() {
    int i = 0;
    int j = 0;
    for (i = 0; i < 5; i++) {
        j = add(j);
    }
    svf_assert(i == 5 && j >= 0);
}
