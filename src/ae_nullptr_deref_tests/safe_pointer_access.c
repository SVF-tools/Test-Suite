#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);

int main() {
  int* p = malloc(sizeof(int));
  *p = 1;
  SAFE_LOAD(p);
}
