#include "aliascheck.h"
int x, *y, z;
void f(int **m);
void main(){

	int **a = &y;

	f(a);


}

void f(int **m){
	if(x){
		*m = &x;
		MUSTALIAS(y,&x);
		NOALIAS(y,&z);
		f(m);
	}
	else{
		*m = &z;
		MUSTALIAS(y,&z);
		NOALIAS(y,&x);
	}

}
