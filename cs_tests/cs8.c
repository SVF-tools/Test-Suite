#include "aliascheck.h"
int obj1,obj2;
void foo(int **p, int **q){

	*p = &obj1;
	*q = &obj2;

}

int main(){

	int **a,**b,*x,*y,*z;
	if(a){
		a = &x;
		b = &y;
	}
	else{
		a = &z;
		b = &z;
	}
	foo(a,b);
    MAYALIAS(x,&obj1);
    MAYALIAS(z,&obj1);
    MAYALIAS(y,&obj2);
    MAYALIAS(z,&obj2);
    NOALIAS(x,&obj2);

}
