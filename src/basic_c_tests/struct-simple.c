/*
 * Alias due to struct assignment
 * Author: Sen Ye
 * Date: 06/09/2013
 */
#include "aliascheck.h"

struct s{
	int *a;
	int b;
};

int main()
{
	struct s s1, s2;
	int x, y;
	s1.a = &x;
	s2.a = s1.a;
	MUSTALIAS(s2.a, &x);
	return 0;
}
