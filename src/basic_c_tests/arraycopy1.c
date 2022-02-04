extern void MAYALIAS(void*,void*);
int main() {
	int a, b;
	int* source[2] = {&a, &b};
	int* x = source[1];
	MAYALIAS(&a,x);
	return 0;
}
