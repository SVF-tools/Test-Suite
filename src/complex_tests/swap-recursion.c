static int n;
void swap(char **a, char **b);
void swap1(char **a, char **b) {
   swap(a, b);
}

void swap(char **a, char **b) {
   char * c;
   c = *a;
   *a = * b;
   *b = c;
   
   n --;
   if (n > 0) swap1(a, b);
}

int main (){
    char b[20];
    char a[20];
    char * p1, *p2;
    char * pa, * pb;

    p1 = a;
    p2 = b;

    n = 4;
    swap (&p1, &p2);
    pa = p2;
    pb = p1;
}


