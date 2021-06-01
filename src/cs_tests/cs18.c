#include "aliascheck.h"
int obj,b;
void bar(int **s){
    *s = &b;
}

void foo(int **p){
	*p = &obj;
	bar(p);
}
main(){
	int **x;
	int *a, *c;
	x=&a; 
	foo(x);
    MUSTALIAS(a,&b);
    NOALIAS(a,&obj);
	x = &c;
	foo(x);
    MUSTALIAS(c,&b);
    NOALIAS(c,&obj);
	
}

