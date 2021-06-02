char * p1, * p2;
void swap() {
   char * c;
   c = p1;
   p1 = p2;
   p2 = c;
}

int main (){
    char b[20];
    char a[20];
    char * pa, *pb;

    p1 = a;
    p2 = b;

    swap ();
    pa = p1;
    pb = p2;
}


