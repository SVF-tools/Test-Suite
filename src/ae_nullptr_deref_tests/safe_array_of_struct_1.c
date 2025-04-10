#include <stdlib.h>

extern void SAFE_LOAD(void *ptr);

struct Data {
    int number;
    char character;
};

int main() {
  struct Data arr[10] = {};
  for (int i = 0; i < 10; ++i) {
      SAFE_LOAD(&arr[i].number);
      SAFE_LOAD(&arr[i].character);
  }
}
