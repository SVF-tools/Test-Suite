#include "aliascheck.h"
void foo(int**a, int*b){

	*a = b;

}


void main(){

	int *p,q,*x,y;
	foo(&p,&q);
    MUSTALIAS(p,&q);
	foo(&x,&y);
    MUSTALIAS(x,&y);
    NOALIAS(x,&q);
    NOALIAS(p,&y);

	*p = 100;

}
