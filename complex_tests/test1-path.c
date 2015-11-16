char h(char * a) {
   *a = 0;
   return 0;
}

char g(char * a) {
    *a = 0;
    return 0;
}

char * f(char * a, int flag) {
   if (flag == 1) h(a);
   else g(a);
}


int main (){
    char b[20];
    char a[20];

    f(b, 1);
    f(a, 2);
}


