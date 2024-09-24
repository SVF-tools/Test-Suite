#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);

int main() {
  int* p = NULL;
  UNSAFE_LOAD(p);
}
