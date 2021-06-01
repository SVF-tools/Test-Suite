#include "aliascheck.h"
int main(){
    int ***m,**n,*z,*y,z1,y1;

    m=&n;
    n=&z;
    *m=&y;
    MUSTALIAS(n,&y);
    NOALIAS(n,&z);
    z=&z1;
    y=&y1;
    ***m=10;
    z=**m;
    NOALIAS(z,&z1);
}
