int g1;
int g2;

const struct {
    int *p1;
    int *p2;
} obj = { &g1, &g2 };

int f() {
    int *p = obj.p1;
    return *p;
} 
