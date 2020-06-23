extern void * malloc(unsigned);


typedef struct{
    int t1;
    int t2;
    int * b;
    int * a;
} basestruct;

void f(basestruct * a) {
    int * t = a->b;
    basestruct * t1 = &(a->b);
    f(t1);

    a->b = a;
}

int main(){
  basestruct t;
  f(&t);
}



