#include "aliascheck.h"

void foo(int**, int*);
main(){
	int **x, *y;
	int  *c, *d,e,f;
	if(x) { x =&c; y =&e;}
	else { x= &d; y = &f;}
	foo(x,y);
    MAYALIAS(c,&e);
    MAYALIAS(d,&f);
    NOALIAS(c,&f);
    NOALIAS(d,&e);
	
}

void foo(int **p, int *q){
	*p = q;
}
