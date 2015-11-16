#include "aliascheck.h"

int main(){
    int **p,*q;
    int *a,*b,c,d;
    if(a){
        p = &a;
        q = &c;
    }
    else if(b) {
        p = &b;
        q = &d;
    }
    else{
      printf("dummy branch\n");
    }
    *p = q;
    MAYALIAS(a,&c);
    MAYALIAS(b,&d);
    NOALIAS(a,&d);
    NOALIAS(b,&c);
}
