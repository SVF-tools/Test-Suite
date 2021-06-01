void swap1(char **a, char **b) {
    char *c;
   c = *a;
   *a = * b;
   *b = c;
}

void swap(char ***a, char ***b) {
    swap1(*a, *b);
}

int main (){
    char b[20];
    char a[20];
    char * p1, *p2, *t1, *t2;
    char ** pa, ** pb;

    p1 = a;
    p2 = b;

    pa = & p1;
    pb = & p2;

    swap (&pa, &pb);

    t1 = *pa;
    *t1 = 0;

    t2= *pb;
    *t2 = 0;

}


