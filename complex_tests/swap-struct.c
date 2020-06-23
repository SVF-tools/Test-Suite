 void swap(char **a, char **b) {
   char * c;
   c = *a;
   *a = * b;
   *b = c;
}

struct ptrstruct{
    char * p1;
    char *p2;
}; 

int main (){
    struct ptrstruct PSt;
    char * pa, * pb;
    char b[20];
    char a[20];
 
    PSt.p1 = a;
    PSt.p2 = b;

    swap (&PSt.p1, &PSt.p2);
    pa = PSt.p2;
    pb = PSt.p1;
}


