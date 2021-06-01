#include "aliascheck.h"

void foo(int** s);
void bar(int** s);
int k;
int main(){

    int **p,*q;
    int *b,*c,e;
    if(e){
        p = &b;
        foo(&q);
    }
    else{
        p = &c;
        q = &e;
    }

    *p = q;
    MAYALIAS(b,&k);
    MAYALIAS(c,&e);
    NOALIAS(b,&e);
    NOALIAS(c,&k);
}

void foo(int**x){
    bar(x);
}

void bar(int**s){
    *s = &k;
}
