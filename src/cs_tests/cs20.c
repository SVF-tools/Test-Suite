#include "aliascheck.h"
int *obj;
int **x,*b,*w,d;
int **z, *a,*y,c;
void Zulu(int**p, int *q);
 
void Xray(){
	x = &b;
	w = &d;
	Zulu(x,w);
    MUSTALIAS(b,&d);
    NOALIAS(b,&c);
}

void Yank(){
	z = &a;
	y = &c;
	Zulu(z,y);
    MUSTALIAS(a,&c);
    NOALIAS(a,&d);
}

void Zulu(int**p,int *q){
	*q = 100;
	*p = q;

}

void main(){

	Xray();
	Yank();

}
