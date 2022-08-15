/*
 * double free
 * Author: Jiawei Ren
 * Date: 02/26/2022
 */

#include "doublefree_check.h"

int main(){
    int *i;
    int *b;
    if(i)
        i = DOUBLEFREEMALLOC(1);
    else
        i = DOUBLEFREEMALLOC(1);
    b = i;
    SAFEFREE(i);
    DOUBLEFREE(b);
}