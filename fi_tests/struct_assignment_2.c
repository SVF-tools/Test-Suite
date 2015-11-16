/*
 * Alias due to struct assignment
 * Author: Sen Ye
 * Date: 06/09/2013
 */
#include "aliascheck.h"

struct s{
	int *a;
	int *b;
};

int main()
{
	struct s s1, s2;
	struct s * p1;
	int x, y;
	s1.a = &x;
	s1.b = &y;
	s2 = s1;
	p1 = &s1;
	MUSTALIAS(p1->a, s2.a);
	MUSTALIAS(p1->b, s2.b);
	return 0;
}
