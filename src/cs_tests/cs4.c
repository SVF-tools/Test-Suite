#include "aliascheck.h"
void foo(int **x,int**y,int **z, int *w){
	int *t;
	*y = w;
	t = *x;
	*z = t;

}

int main(){

	int *a,*b,*c,d,*p,*q,r,a1;
    a = &a1;
	foo(&a,&b,&c,&d);
    MUSTALIAS(b,&d);
    MUSTALIAS(c,&a1);
	foo(&p,&p,&q,&r);
    MUSTALIAS(p,&r);
    MUSTALIAS(p,q);
    NOALIAS(b,p);
    NOALIAS(c,p);
}
