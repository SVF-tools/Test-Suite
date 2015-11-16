#include "aliascheck.h"
int obj;
void foo(int**, int**);
main(){
	int **x, **y;
	int *a, *b, *c, *d,*e;
	x=&a; y =&b; 
	foo(x,y);
    MUSTALIAS(a,&obj);
	x = &c;
	foo(x,y);
    MUSTALIAS(c,&obj);
	
}

void foo(int **p, int **q){
	*p = &obj;
}
