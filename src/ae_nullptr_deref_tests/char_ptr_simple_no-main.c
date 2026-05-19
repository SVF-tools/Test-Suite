#include <stdlib.h>

extern void UNSAFE_LOAD(void *ptr);

int no_main_char_ptr_simple() {
  char *p = NULL;
  UNSAFE_LOAD(p);
}
