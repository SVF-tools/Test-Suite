char g1;
char g2;

int cond();

void f1(char **p) {
        //char *tmp = *p;
        if (cond()) *p = &g2;
}

char *f2() {
        char *p = &g1;
            f1(&p);
                return p;
} 
