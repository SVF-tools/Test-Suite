#include <stdio.h>
class K{
public:
virtual char* fater(){
 return "fd";
}
};

class F: public K{
public:
char* foo(char** q){
  char* t = *q;
  return t;
}
char *getinput(){
return "fdaf";
}
};

int main(){
  K* k = new F();
  F f;
  char * a;
  char **q = &a;
  char* p = f.getinput();
  k->fater();
  *q = p;
  char* r = f.foo(q);
  printf("%s\n",r);
 }
