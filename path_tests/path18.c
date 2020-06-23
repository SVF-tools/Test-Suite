#include "aliascheck.h"
int x,y,*q,*f,*e,d;

void foo(int **p){
	f = &x;
	if(x){
		p = &e;
		f = &y;
	}

	*p = f;
    MAYALIAS(q,&x);
    MAYALIAS(e,&y);
    NOALIAS(q,&y);
    NOALIAS(q,&d);
    NOALIAS(e,&x);
}



int main(){
	int **a,c;
	a = &q; f = &d;	
	foo(a);
}

