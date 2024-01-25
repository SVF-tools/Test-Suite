//
// Created by chengxiao on 8/01/24.
//

#include <stdio.h>
#include <stdlib.h>

// safe malloc
void* TYPE_MALLOC(int n, int eleNum){
    return malloc(n);
}