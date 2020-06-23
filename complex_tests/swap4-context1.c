    char b[20];
    char a[20];
 

void swap(char **a, char **b) {
   char * c;
   c = *a;
   *a = * b;
   *b = c;
}

void f1(char **a, char **b) {
  swap(a, b);
}

void f2(char **a, char **b) {
  swap(a,b);
  f1(b, a);
}

void f3(char **a, char **b) {
  f1(a, b);
  f2(b, a);
}

void f5(char **a, char **b) {
  f3(a, b);
  f2(b, a);
}

void f8(char **a, char **b) {
  f3(a, b);
  f5(a, b);
}


void g(char **a, char **b) {
   swap(a, b);
   swap(a, b);
}

void h(char **a, char **b) {
   f8(a, b);
   f5(a, b);
   g(a, b);
}

int main (){
    char * p1, *p2;
    char * pa, * pb;

    p1 = a;
    p2 = b;

    h (&p1, &p2);
    g (&p2, &p1);
    f5 (&p1, &p2);
    g (&p2, &p1);
    pa = p2;
    pb = p1;
}


