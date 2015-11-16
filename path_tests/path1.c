#include "aliascheck.h"

void foo(int**, int*);
main(){
	int **x, *y;
	int  *c, *d,e,f;
	if(x) { x =&c; y =&e;}
	else { x= &d; y = &f;}
	foo(x,y);
    MUSTALIAS(c,&e);
    MUSTALIAS(d,&f);
    NOALIAS(c,&f);
    NOALIAS(d,&e);
	
}

void foo(int **p, int *q){
	*p = q;
}
