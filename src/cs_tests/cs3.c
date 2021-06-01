#include "aliascheck.h"
void foo(int **p, int **q, int **r,int *s){

	*r = *p;
	*q = s;

}


void main(){

	int **a,**b,**c,**d,**e,**f,*x,*y,*z,*w,*g,*k,x1,y1,z1,w1,k1,g1;
	x = &x1;
	y = &y1;
	z = &z1;
	w = &w1;
	g = &g1;
	k = &k1;

	a = &x;
	b = &y;
	c = &z;

	foo(a,b,c,k);
    MUSTALIAS(x,z);
    MUSTALIAS(y,&k1);
	d = &w;
	e = &w;
	f = &g;
	foo(d,e,f,k);
    NOALIAS(w,g);
    MUSTALIAS(w,&k1);
    NOALIAS(x,w);
    NOALIAS(z,g);
    MUSTALIAS(w,y);

}
