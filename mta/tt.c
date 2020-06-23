/*
 *  * Simple alias check
 *   * Author: pengd 
 *    * Date: 07/07/2015
 *     */
#include "pthread.h"

pthread_t t1;
int **gp;
void *foo2(void *a) {
    //int* a;
    gp = &a;
    return a;
}

int main(){
	int* b;
	//gp = &b;
	pthread_create(&t1, NULL, foo2, &b);
	//foo2(NULL);
	print ("%d",*gp);
	return 1;
}
// todo
