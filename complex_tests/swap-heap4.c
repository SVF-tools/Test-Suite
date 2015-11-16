void * malloc(unsigned);
char ga[20];
void swap(char **a, char **b) {
   char * c;
   c = *a;
   *a = * b;
   *b = c;
}

void * mymalloc(unsigned i) {
   return malloc(i);
}

void * my_malloc(unsigned i, char **ret) {
   char * p;
   char * q;
   p = mymalloc(i);
   q = mymalloc(i + 20);
   swap(&p, &q);
   *ret = q;
   return p;
}

int main (){
    char * p1, *p2;
    char * pa, * pb;

    pa = my_malloc(10, &p1);
    pb = my_malloc(20, &p2);

    swap (&pa, &pb);
    swap (&p1, &p2);

    pa = p2;
    pb = p1;
}


