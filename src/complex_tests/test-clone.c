
extern void * malloc(unsigned);

char * ptrs[10];
void  my_malloc(unsigned idx, unsigned length) {
    char * a = malloc(length);
    free (ptrs[idx]);
    ptrs[idx] = a;
}

char * my_malloc1(unsigned idx, unsigned lenght) {
    static char * a = 0;

    if (a != 0) 
        free(a);
    a = malloc(idx);
    return a;
}


unsigned malloc2(unsigned idx, unsigned length){
    unsigned curidx;
    my_malloc(idx, length);
    my_malloc1(idx+1, length);
    curidx = idx +2; 
    if (curidx < 8) 
        return malloc2(curidx, length);
    return curidx;
}

int main () {

    malloc2(1, 10);
}


