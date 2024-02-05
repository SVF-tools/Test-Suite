int main() {
	int a, b;
	int* source[2] = {&a, &b};
	int* x = source[1];
	svf_assert(x==&b);
	return 0;
}
