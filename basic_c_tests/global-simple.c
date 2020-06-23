/*
 * Global variables test.
 * Author: Sen Ye
 * Date: 03/05/2014
 */
#include "aliascheck.h"

int a_int = 10;
int* p_int = &a_int;
int** pp_int = &p_int;

int main() {
	int b_int = a_int;
	int* q_int = p_int;
	int** qq_int = pp_int;
	MUSTALIAS(*qq_int, q_int);
	MUSTALIAS(q_int, &a_int);
	return 0;
}
