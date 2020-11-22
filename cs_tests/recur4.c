#include "aliascheck.h" 
int **x, *y;
int z;
void f(int **p);
void main(){
	x = &y;
	f(x);
}


void f(int **p){
	int k;
	y = &k;
	if (z){
		*p = &z;
		MUSTALIAS(y,&z);
		NOALIAS(y,&k);

		f(p);
	}
	/// y will not alias to &z as the value flow
	/// of y after it is updated at "*p=&z" will
	/// flow into f(p) again and then be updated
	/// by the first statement "y=&k".
	NOALIAS(y,&z);
	MAYALIAS(y,&k);

}

