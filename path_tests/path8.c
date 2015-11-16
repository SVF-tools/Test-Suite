#include "aliascheck.h"

int main(){

    int **p,*q;
    int *b,*c,d,e;

    p = &c;

c1:    if(e){
           p = &b;
           q = &d;
       }
       else if(b) {
           q = &e;
       }
       else if(c){
          printf("dummy branch\n");
       }
       else{
           goto c1;
       }

       *p = q;
       MAYALIAS(p,&c);
       MAYALIAS(p,&b);
       MAYALIAS(c,&e);
       MAYALIAS(b,&d);
       NOALIAS(c,&d);
       NOALIAS(b,&e);
}
