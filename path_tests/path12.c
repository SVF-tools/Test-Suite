#include "aliascheck.h"

int obj, t,s;
void foo(int**, int**);

void main(){
	int **x, **y;
	int *a, *b, *c, *d,*e;
	e = &t; d = &obj;
	c = &s;
	if(t) { x =&c; y =&e;}
	else { x= &d; y = &d;}
    foo(x,y);
    NOALIAS(c,&obj);
    NOALIAS(d,&t);
	
}

void foo(int **p, int **q){
	*p = *q;
}
