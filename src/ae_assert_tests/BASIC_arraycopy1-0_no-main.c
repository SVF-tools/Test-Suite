int no_main_BASIC_arraycopy1_0() {
	int a, b;
	int* source[2] = {&a, &b};
	int* x = source[1];
	svf_assert(x==&b);
	return 0;
}
