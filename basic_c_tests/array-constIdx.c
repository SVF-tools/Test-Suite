/*
 * Alias with array
 * Author: Sen Ye
 * Date: 06/09/2013
 */
#include "aliascheck.h"

struct MyStruct {
	int * f1;
	int * f2;
};

int main() {
	struct MyStruct s[2];
	int a,b;
	s[0].f1 = &a;
	s[1].f1 = &b;

	// Different fields of different elements in a 
	// certain array are treated as different objects.
	NOALIAS(s[0].f1, s[1].f2);
	MAYALIAS(s[0].f1, s[1].f1);

	return 0;
}
