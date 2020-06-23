#include "aliascheck.h"

int main(){

    int **p,*q;
    int *a,*b,c,d;
    p = &a;
    if(p){
        if(c){
            q = &c;
        }
    }
    else{
        p = &b;
        q = &d;
    }
    if(d){
        *p = q;
    }
    MAYALIAS(a,&c);
    MAYALIAS(b,&d);
    NOALIAS(a,&d);
    NOALIAS(b,&c);


}
