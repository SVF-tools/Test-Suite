char *p;
char *q;

char swap() {
    char * c = p;
    p = q;
    q = c;
}


void recursion(unsigned i) {
    if (i == 0) {
        return;
    }
    swap();
    recursion(i--);
}

int main () {
    char a[10];
    char b[10];

    p = a;
    q = b;

    recursion(10);
}


