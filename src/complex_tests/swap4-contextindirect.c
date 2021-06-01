    char b[20];
    char a[20];
  

void swap1(char **a, char **b) {
    char * c;
    c = *a;
    *a = *b;
    *b = c;
}

void swap(char ***a, char ***b) {
   char ** c;
   char ** d;

   c =*a;
   d =*b;
   swap1(c, d);
}

void f(char ***a, char ***b) {
  swap(a, b);
}

void g(char ***a, char ***b) {
   swap(a, b);
   swap(a, b);
}

void h(char ***a, char ***b) {
   f(a, b);
   f(a, b);
   g(a, b);
}

int main (){
    char ** p1, ** p2;
    char * pa, * pb;
    char * pa1, *pb1;
 
    pa = a;
    pb = b;

    p1 = & pa;
    p2 = & pb;


    h (&p1, &p2);
    g (&p1, &p2);
    f (&p1, &p2);
    g (&p1, &p2);

    pa1 = *p2;
    pb1 = *p1;
}


