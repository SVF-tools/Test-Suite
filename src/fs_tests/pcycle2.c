#include "aliascheck.h"
int main(){

    int **a,**b,**c;
    int k;
    a=&b;
    *a=&c;
    *b=&a;
    MUSTALIAS(c,&a);
    MUSTALIAS(b,&c);
    MUSTALIAS(a,&b);
    
}
