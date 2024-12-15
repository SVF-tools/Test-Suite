#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);

int main() {
  int arr[10] = {0};
  for (int i = 0; i < 10; ++i)
      SAFE_LOAD(&arr[i]);
}
