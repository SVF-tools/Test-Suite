void (*p)(char **, char **); 

void swap(char **a, char **b) {
   char * c;
   c = *a;
   *a = * b;
   *b = c;
}

void registerhandle( void (*f)(char **, char **) ) {
    p = f;
}

int main (){
    char * p1, *p2;
    char * pa, * pb;
    char b[20];
    char a[20];
 
    p1 = a;
    p2 = b;

    registerhandle(swap);

    (*p)(&p1, &p2);

    pa = p2;
    pb = p1;
}


