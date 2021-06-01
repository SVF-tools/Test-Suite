char * f(char * a) {
   char * b ;

   b = a;
    *(b++) = 1;
   return b;
}

char * g(char * a) {
    *a = 0;
    return f(a);
}

int main (){
    char a[10];
    char b[20];
    char * c;

    f(a);
    c = f(b);
    g(c);
}


