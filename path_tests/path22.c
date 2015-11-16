#include "aliascheck.h"

void foo(int ***,int**);
int obj;
int main(){

    int ***p,**q, **a, **b, *c, *m,*n,d;
    m = &d;
    a = b = &c;
    if(a){
        p = &a;
        q = &c;
        foo(p,q);
    }
    else{
        p = &b;
        q = &c;
        foo(p,q);
    }

   *a = m;
   n = *b;
   MUSTALIAS(a,b);
   MUSTALIAS(m,n);
}

void foo(int ***x,int **y){
    *x = y;
}
