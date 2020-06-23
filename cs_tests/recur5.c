#include "aliascheck.h"
int* x, x1;
void f(int **m){
int **n,*y,*k,z,r;
   n = &y;
   y = &z;
   if(z==1){
	*n=&r;
	MUSTALIAS(y,&r);
	EXPECTEDFAIL_NOALIAS(y,&z);
	k = *n;
	MUSTALIAS(k,&r);
	EXPECTEDFAIL_NOALIAS(k,&z);
	f(n);
   }
}

int main(){
	x=&x1;
	f(x);
}
