/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"
void bar(int***k, int***s){

	*k = *s; 

}

int main(){
	int *p1,*q1,*r1,*a1,*b1,*c1,q2,a2;
	int **p = &p1;
	int **q = &q1;
	q1 = &q2;
	bar(&p,&q);
	TBHC_NOALIAS(p,&p1);
}
