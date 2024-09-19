#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);

int main() {
  int arr[1] = {0};
  SAFE_LOAD(arr);
}
