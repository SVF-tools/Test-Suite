#include "aliascheck.h"
int y,*q,*r,*f,*e,c,d;

void foo(int **p){

    if(y){
		p = &e;
		f = &y;
	}

	*p = f;
    MAYALIAS(q,&d);
    MAYALIAS(r,&c);
    MAYALIAS(e,&y);
    NOALIAS(q,&y);
    NOALIAS(r,&y);
}



int main(){
	int **a,**b;
    e = 0;
	a = &q; f = &d;	
	foo(a);
    b = &r; f = &c;
    foo(b);
    NOALIAS(r,&d);
    NOALIAS(q,&c);
    NOALIAS(e,&d);
    NOALIAS(e,&c);
}

