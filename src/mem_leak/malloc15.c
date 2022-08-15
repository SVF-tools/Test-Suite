/*
 * Never free
 * Author: Yule Sui
 * Date: 02/04/2014
 */

#include "memleak_check.h"

int *foo(){

	return NFRMALLOC(1);

}


int main(){

int *p = foo();
}
