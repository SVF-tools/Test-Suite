extern void NOALIAS(void*,void*);

struct S {int f0; int f1; int f2;};

int main()
{
	struct S s;
	void *a, *b, *c, *d;
	
	a = &s;
	b = &((struct S*) a)->f1;
	c = &((struct S*) b)->f1;
	d = &((struct S*) a)->f1;
	
	NOALIAS(c,d);

	return 0;
}

