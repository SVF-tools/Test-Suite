void swap(char **a, char **b, int flag) {
   char * c;
   if (flag == 1) {
      c = *a;
      *a = * b;
      *b = c;
   }
}

int main (){
    char b[20];
    char a[20];
    char * p1, *p2;
    char * pa, * pb;

    p1 = a;
    p2 = b;

    swap (&p1, &p2, 1);
    swap (&p1, &p2, 1);
    swap (&p1, &p2, 1);
    swap (&p1, &p2, 0);
    pa = p2;
    pb = p1;
}


