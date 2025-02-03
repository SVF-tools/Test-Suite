#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {
  char *p = NULL;
  UNSAFE_LOAD(p);
}
