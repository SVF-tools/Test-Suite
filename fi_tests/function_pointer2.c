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

void my_vfprintf(struct MYFILE *pts) {
	  printf("Executing bar\n");
	  int *p = &g;
	    pts->pt(p);
}

int my_vsnprintf() {
	  struct MYFILE pts = { .pt = my_sn_write };
	    my_vfprintf(&pts);
	      return 0;
}

int main() {
	  my_vsnprintf();
	    return 0;
}

