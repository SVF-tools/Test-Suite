#include "aliascheck.h"
int g;
int* obj = &g;
void Zulu(int**p, int *q);
 
void Xray(){

	int **x,*b,*w,d;
	x = &b;
	w = &d;
	Zulu(x,w);
    NOALIAS(b,w);
    MUSTALIAS(b,&g);
}


void Zulu(int**p,int *q){

	*p = q;
    *p = obj;
}

void main(){

	Xray();

}
