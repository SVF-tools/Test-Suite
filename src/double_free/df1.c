/*
 * double free
 * Author: Jiawei Ren
 * Date: 02/26/2022
 */

#include "doublefree_check.h"

int main(){
    int *i = SAFEMALLOC(sizeof(int));
    SAFEFREE(i);
    i = SAFEMALLOC(sizeof(int));
    SAFEFREE(i);
}