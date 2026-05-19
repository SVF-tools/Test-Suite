extern void svf_assert(int);
int no_main_BASIC_arraycopy2_0() {
	char source[2] = {'A','B'}; //include terminating character
	char x = source[1];
	svf_assert(x=='B');
	return 0;
}
