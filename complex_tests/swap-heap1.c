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
   p = mymalloc(i);
   *ret = p;
   return p;
}

int main (){
    char * p1, *p2;
    char * pa, * pb;

    my_malloc(10, &p1);
    my_malloc(20, & p2);
    swap(&p1, &p2);
    pa = p2;
    pb = p1;
}


