#include "aliascheck.h"
int main(){
    int **p,*q;
    int *a,*b,c,d,e;
    q = &c;
    if(a){
        p = &a;
        if(c){
            q = &d;
        }
    }
    else{
        p = &b;
        q = &e;
    }

    *p = q;
    MAYALIAS(a,&c);
    MAYALIAS(a,&d);
    MAYALIAS(b,&e);
    NOALIAS(a,&e);
    NOALIAS(b,&c);
    NOALIAS(b,&d);

}
