/*
 * double free
 * Author: Jiawei Ren
 * Date: 02/26/2022
 */

#include "doublefree_check.h"

int main(){
    int *i = SAFEMALLOC(sizeof(int));
    int *b = SAFEMALLOC(sizeof(int));
    SAFEFREE(i);
    i = DOUBLEFREEMALLOC(sizeof(int));
    SAFEFREE(i);
    DOUBLEFREE(i);
    SAFEFREE(b);
}