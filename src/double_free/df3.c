/*
 * double free false positive
 * Author: Jiawei Ren
 * Date: 02/26/2022
 */

#include "doublefree_check.h"

void foo(int *p){

    SAFEFREE(p);
}
void foo2(int *p){

    DOUBLEFREE(p);
}
int main(){
    int *i = DOUBLEFREEMALLOC(sizeof(int));
    foo(i);
    int *j = SAFEMALLOC(sizeof(int));
    foo(j);
    foo2(i);
}