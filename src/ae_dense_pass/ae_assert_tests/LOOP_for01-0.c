//
// Created by Jiawei Wang on 4/27/22.
//

#include "stdbool.h"
extern void svf_assert(bool);
extern void svf_print(int, char*);
int main() {
    int i = 0;
    int j = 0;
    // bound 5
    for (i = 0; i < 5; i++) {
        j++;
    }
    svf_assert(i == 5 && j >= 0);
}
