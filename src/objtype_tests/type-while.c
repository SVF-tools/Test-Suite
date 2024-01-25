#include "type_check.h"

struct MyStruct {
    int * f1;
    struct MyStruct * next;
};

int main() {
    struct MyStruct * p = (struct MyStruct *) TYPE_MALLOC (sizeof(struct MyStruct), 2);

    int num = 10;
    while (num) {
        p->next = (struct MyStruct *) TYPE_MALLOC (sizeof(struct MyStruct), 2);
        p->next->f1 = (int *) TYPE_MALLOC (sizeof(int), 2);
        p = p->next;
    }
    struct MyStruct *q = p;
    return 0;
}