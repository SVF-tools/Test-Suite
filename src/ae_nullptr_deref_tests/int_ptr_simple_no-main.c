#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);

int no_main_int_ptr_simple() {
  int* p = NULL;
  UNSAFE_LOAD(p);
}
