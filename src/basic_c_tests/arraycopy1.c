extern void NOALIAS(void*,void*);
int main() {
	int a, b;
	int* source[2] = {&a, &b};
	int* x = source[1];
	NOALIAS(&a,x);
	return 0;
}
