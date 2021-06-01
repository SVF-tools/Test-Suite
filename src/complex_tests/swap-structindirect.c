struct ptrstruct{
    int temp;
    char * p1;
    char *p2;
}; 

void swap(struct ptrstruct ** pstruct) {
   struct ptrstruct *P = *pstruct;
   char * c;
   c = P->p1;
   P->p1 = P->p2;
   P->p2 = c;
}

 

int main (){
    struct ptrstruct PSt;
    struct ptrstruct * pstruct = &PSt;
    char * pa, * pb;
    char b[20];
    char a[20];
 
    PSt.p1 = a;
    PSt.p2 = b;

    swap (&pstruct);
    pa = PSt.p2;
    pb = PSt.p1;
}


