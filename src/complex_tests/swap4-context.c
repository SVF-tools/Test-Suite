    char b[20];
    char a[20];
 

void swap(char **a, char **b) {
   char * c;
   c = *a;
   *a = * b;
   *b = c;
}

void f(char **a, char **b) {
  swap(a, b);
}

void g(char **a, char **b) {
   swap(a, b);
   swap(a, b);
}

void h(char **a, char **b) {
   f(a, b);
   f(a, b);
   g(a, b);
}

int main (){
    char * p1, *p2;
    char * pa, * pb;

    p1 = a;
    p2 = b;

    h (&p1, &p2);
    g (&p1, &p2);
    f (&p1, &p2);
    g (&p1, &p2);
    pa = p2;
    pb = p1;
}


