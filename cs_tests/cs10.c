#include "aliascheck.h"
int obj, t,s;
void foo(int**, int**);
main(){
	int **x, **y;
	int *a, *b, *c, *d,*e;
	x=&a; y =&b; 
	foo(x,y);
    MUSTALIAS(b,&obj);
	*b = 5;
	c=&s;
	//a=c;
	if(t) { x =&c; y =&e;}
	else { x= &d; y = &d;}
	foo(x,y);
    MAYALIAS(e,d);
    MAYALIAS(e,&obj);
	*e = 10;
	
}

void foo(int **p, int **q){
	*q = &obj;
}
