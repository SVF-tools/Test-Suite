char * h(char * a) {
   *a = 0;
   return a;
}

char * f(char * a, char * b, unsigned flag) {
   if (flag == 1) return h(a);
   else return h(b);
}


int main (){
    char b[20];
    char a[20];
    int flag = a[0];
    char * pa;
    char * pb;

    pa = f(a, b, 0);
    pb = f(a, b, 1);
}


