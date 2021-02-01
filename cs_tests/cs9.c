#include "aliascheck.h"
int obj, t,s;
int *k =&s;
void foo(int**, int**);
main(){
	int **x, **y;
	int *a, *b, *c, *d,*e;
    a = &t;
	x=&a; y =&b; 
	foo(x,y);
    NOALIAS(a,b);
    MUSTALIAS(b,&obj);
	*b = 5;
	c=&t;
	c=&s;
	a=c;
    MUSTALIAS(a,c);
	if(t) {c=&obj; x =&c; y =&e;}
	else { x= &d; y = &d;}
	e = &t;
	foo(x,y);
    MAYALIAS(c,d);
    MAYALIAS(d,&obj);
    MAYALIAS(a,c);
    NOALIAS(a,d);
    MAYALIAS(c,d);
	*e = 10;
	
}

void foo(int **p, int **q){
	*p = *q;
	*q = &obj;
}
