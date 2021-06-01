#include <stdio.h>
#include "aliascheck.h"
int g;
static int my_sn_write(int* p) {
    printf("Executing my_sn_write\n");
    MAYALIAS(&g,p);
    return 0;
}

struct MYFILE {
    int (*pt) (int* p);
};

struct MyStruct {
    const struct MYFILE *myfile;
};

const struct MYFILE pts = { .pt = my_sn_write };
const struct MyStruct ms = { .myfile = &pts };

void my_vfprintf(const struct MyStruct *ms) {
    printf("Executing bar\n");
    int *p = &g;
    ms->myfile->pt(p);
}

int main() {
    my_vfprintf(&ms);
    return 0;
}

