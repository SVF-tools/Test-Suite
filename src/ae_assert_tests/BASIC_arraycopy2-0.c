extern void svf_assert(int);
int main() {
	char source[2] = {'A','B'}; //include terminating character
	char x = source[1];
	svf_assert(x=='B');
	return 0;
}
