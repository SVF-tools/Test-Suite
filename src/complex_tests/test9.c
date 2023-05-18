extern void swapExtCallStmt(char **a, char **b);

void swap(char **a, char **b) {}

int main (){
    char * p1, *p2;
    char * pa, * pb;
    char b[20];
    char a[20];
 
    p1 = a;
    p2 = b;

    swapExtCallStmt(&p1, &p2);
    pa = p2;
    pb = p1;
}
