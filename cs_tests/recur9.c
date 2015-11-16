#include "aliascheck.h"
int z;
void foo(int **a);
void bar(int **q){
    int** a = malloc(10);
    foo(a);
}

void foo(int **a){
    *a = &z;
    bar(a);
}




int main(){
    int** a,*b,*c,b1,c1;
    b = &b1;
    a = &b;
    foo(a);
    MUSTALIAS(b,&z);
    EXPECTEDFAIL_NOALIAS(b,&b1);
    a = &c;
    foo(a);
    MUSTALIAS(c,&z);
    NOALIAS(c,&c1);
}
