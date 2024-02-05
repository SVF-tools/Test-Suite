extern void svf_assert(int);
int a[2]={1,2};
int main() {
	//char source[5] = "hello";
	svf_assert(a[1]==2);
	return 0;
}
