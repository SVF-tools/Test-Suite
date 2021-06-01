#include "aliascheck.h"
int obj;
void foo(int **p, int **q, int **r){


	*r = *p;
	*q = &obj;

}


void main(){

	int **a,**b,**c,**d,**e,**f,*x,*y,*z,*w,*k,x1,y1,z1,w1,k1;
	x = &x1;
	y = &y1;
	z = &z1;
	w = &w1;
	k = &k1;

	a = &x;
	b = &y;
	c = &z;
	if(a){

		d = &w;
		e = &w;
		f = &k;
	}
	foo(a,b,c);
    MUSTALIAS(x,z);
    MUSTALIAS(y,&obj);
	foo(d,e,f);
    NOALIAS(w,k);
    MAYALIAS(w,&obj);
    NOALIAS(x,w);
    NOALIAS(z,k);
    MAYALIAS(y,w);

}
