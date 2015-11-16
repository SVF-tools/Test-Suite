void swap(char ***a, char ***b) {
    char **a1, **b1;
    char *c;
    a1 = *a;
    b1 = *b;

    c = *a1;
    *a1 = *b1;
    *b1 = c;
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
    *t1 = 1;

    t2= *pb;
    *t2 = 0;

}


