#include "aliascheck.h"

void foo(int**,int* );
int main(){

    int **p,*q;
    int *a,*b,c,d;
    if(a){
        p = &a;
        q = &c;
        foo(p,q);
    }
    else{
        p = &b;
        q = &d;
        foo(p,q);
    }

    *p = q;
    MAYALIAS(a,&c);
    MAYALIAS(b,&d);
    NOALIAS(a,&d);
    NOALIAS(b,&c);
}

void foo(int**x,int *y){
    *x = y;
}

