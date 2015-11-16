#include "aliascheck.h"


int main(){

    int **p,**q;
    int **x,**y;
    int *a,*b,*x1,a1,b1;
    int *m,*n,n1;
    /// Note that n needs to be initialized
    n = &n1;
    a = &a1;
    b = &b1;
    x = y = &x1;
    p = q = &a;
    if(a){
        p = x;
        q = y;
    }

    *p = n;
    m = *q;

    MAYALIAS(p,&a);
    MAYALIAS(p,&x1);
    NOALIAS(m,&a1);
    NOALIAS(m,&x1);
    MUSTALIAS(n,m);

}
