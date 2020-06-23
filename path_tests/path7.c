#include "aliascheck.h"

int main(){

    int **p,*q;
    int *b,*c,d,e;

    p = &c;
    q = &e;

    if(d){
        p = &b;
    }
    else{
        q = &d;
    }

    *p = q;

    MAYALIAS(b,&e);
    MAYALIAS(c,&d);
    NOALIAS(c,&e);
    NOALIAS(b,&d);
}
