extern void svf_assert(int);
int main(){

  int a[3];
  a[0] = 0;
  a[1] = 1;
  a[2] = 2;
  int i = 1;
  svf_assert(a[i]==1);

}
