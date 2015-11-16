#include "aliascheck.h"
int *x,y,z;

void f();

int main(){
    f();
    *x=100;
}

void f(){
    
    if(z){
	x=&y;
	f();
	x=&z;
	f();
	MUSTALIAS(x,&z);
	EXPECTEDFAIL_NOALIAS(x,&y);
    }
	MAYALIAS(x,&z);
	MAYALIAS(x,&y);
}
