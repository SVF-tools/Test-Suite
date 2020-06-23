char * g(char * a) {
    *a = 0;
    return a;
}

char * f(char * a) {
   char * b ;

   b = a;
    *(b) = 0;
   return g(b);
}

char * c;
int main (){
    char b[20];
    char a[20];
    char * p1, *p2;

    p1 = a;
    p2 = b;

    swap (&p1, &p2);
    c = b;
    c = f(c);
    g(c);
}


