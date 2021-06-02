char *p;

char accessA(unsigned i) {
  return *(p+i);
}


void recursion(unsigned i) {
    if (accessA(i) > 0) return;
    recursion(i++);
}
int main () {
    unsigned i = 0;
    unsigned a[10];
    p = a;
    recursion(0);
}


