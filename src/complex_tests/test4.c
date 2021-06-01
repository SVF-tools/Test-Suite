extern char * malloc(int);
char * f(char * a) {
   char * c;
   c = malloc(10*sizeof(char));
   *(c++)= *a;
   return c;
}

char * g(char * a) {
    *a = 0;
    return f(a);
}
char * h(char *a) {
    return g(a);
}
char * i(char *a) {
    return g(a);
}

int main (){
    char a[10];
    char * c;

    if (a[0] == 1) c=h(a);
    else c=i(a);
}


