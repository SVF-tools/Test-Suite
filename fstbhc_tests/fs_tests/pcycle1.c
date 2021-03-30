/* Copied from fs_tests/ and modified to use TBHC macros. */
#include "aliascheck.h"
int main(){
    int ***m,**n,*z,*y,z1,y1;

    m=&n;
    n=&z;
    *m=&y;
    TBHC_MUSTALIAS(n,&y);
    TBHC_NOALIAS(n,&z);
    z=&z1;
    y=&y1;
    ***m=10;
    z=**m;
    TBHC_NOALIAS(z,&z1);
}
