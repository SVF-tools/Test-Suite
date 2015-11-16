#include "aliascheck.h"
int* x,y;
void f(int *m){
	MUSTALIAS(m,&y);
	int *n;
	if(y==1){
		n=&y;

		f(n);
	}
}

int main(){
	x=&y;
	f(x);
}
