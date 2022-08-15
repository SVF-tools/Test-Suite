/*
 * double free
 * Author: Jiawei Ren
 * Date: 02/26/2022
 */

#include "doublefree_check.h"

int main(){
    int *i = DOUBLEFREEMALLOC(sizeof(int));
    int j = 0;
    if (j == 1){
        SAFEFREE(i);
    } else {
        SAFEFREE(i);
    }
    DOUBLEFREE(i);
}