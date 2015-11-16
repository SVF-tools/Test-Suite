#include "aliascheck.h"
void foo(int*,int*);
main(){
	int*x, *y;
	int a,b, c;
	if(c)x=&a; 
	else x=&b;
    MAYALIAS(x,&a);
    MAYALIAS(x,&b);
	foo(x,y);
	x = &c;
	foo(x,y);
    MUSTALIAS(x,&c);
    NOALIAS(x,&a);
    NOALIAS(x,&b);
	
}

void foo(int *p,int*q){
	*p = 100;
}
