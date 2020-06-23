char *p;
char *q;

void recursion (unsigned);
void swap(unsigned);

void swap(unsigned i) {
    char * c = p;
    p = q;
    q = c;

    recursion (i --);
}


void recursion(unsigned i) {
    if (i == 0) {
        return;
    }
    swap(i);
}

int main () {
    char a[10];
    char b[10];

    p = a;
    q = b;

    recursion(10);
}


