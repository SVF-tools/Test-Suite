/*
 * pass value to globals
 *
 * Author: Yule Sui
 * Date: 02/04/2014
 */

#include "memleak_check.h"

int *g;
int main(){

	int *p = SAFEMALLOC(1);
	g = p;
	printf("%d,%d",g,p);
}
