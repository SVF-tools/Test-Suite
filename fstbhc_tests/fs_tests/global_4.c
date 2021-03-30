/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"
int g;
int* obj = &g; 
void Zulu(int**p, int *q);

void Xray(){

	int **x,*b,*w,d;
	x = &b; 
	w = &d; 
	Zulu(x,w);
	TBHC_NOALIAS(b,w);
	TBHC_MUSTALIAS(b,&g);
}


void Zulu(int**p,int *q){
	*p = q;
	*p = obj;
}

int main(){
	Xray();
	return 0;
}
